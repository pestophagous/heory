#include "collection.h"

namespace heory
{
namespace tests
{
    Collection::Collection(
        const QQmlApplicationEngine*, Random*, QmlMessageInterceptor*, const CliOptions* )
    {
    }

    Collection::~Collection()
    {
    }

    void Collection::Start()
    {
    }

    bool Collection::PollForDoneness()
    {
        return true; // for the inert collection, we indeed wish to finish immediately
    }
} // namespace tests
} // namespace heory
