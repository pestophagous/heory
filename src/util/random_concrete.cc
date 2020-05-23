#include "random_concrete.h"

#include <map>
#include <memory>
#include <random>
#include <utility>

#include "util-assert.h"

namespace heory
{
namespace
{
    constexpr std::mt19937::result_type CONST_SEED = 3;
} // namespace

struct Distribution
{
    Distribution( int lower, int upper, bool repeatableSeed )
        : gen( repeatableSeed ? CONST_SEED : rd() ), dis( lower, upper )
    {
        FASSERT(
            upper > lower, "we need an ordered pair of distinct values, least to greatest" );
    }

    int GetNext()
    {
        return dis( gen );
    }

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

/*static*/ std::unique_ptr<RandomConcrete> RandomConcrete::RandomConcreteForProduction()
{
    return std::unique_ptr<RandomConcrete>( new RandomConcrete( false /*repeatableSeed*/ ) );
}

/*static*/ std::unique_ptr<RandomConcrete> RandomConcrete::RandomConcreteForTests()
{
    return std::unique_ptr<RandomConcrete>( new RandomConcrete( true /*repeatableSeed*/ ) );
}

struct RandomConcrete::Impl
{
    std::map<std::pair<int, int>, std::unique_ptr<Distribution>> m_distributions;
};

RandomConcrete::RandomConcrete( const bool repeatableSeed )
    : m_usingRepeatableSeed( repeatableSeed ), m_impl( std::make_unique<Impl>() )
{
}

RandomConcrete::~RandomConcrete()
{
}

int RandomConcrete::GetNextFromNToMInclusive( const int n, const int m )
{
    if( n >= m )
    {
        FFAIL( "we need an ordered pair of distinct values, least to greatest" );
        return 0;
    }

    const auto pair = std::make_pair( n, m );
    const auto finder = m_impl->m_distributions.find( pair );

    if( finder != m_impl->m_distributions.end() )
    {
        return finder->second->GetNext();
    }
    else
    {
        m_impl->m_distributions[ pair ]
            = std::make_unique<Distribution>( n, m, m_usingRepeatableSeed );
        return m_impl->m_distributions[ pair ]->GetNext();
    }
}

} // namespace heory
