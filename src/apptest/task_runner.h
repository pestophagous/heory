//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_TASK_RUNNER_H
#define PROJECT_APP_GUI_TESTS_TASK_RUNNER_H

#include "src/apptest/task.h"

namespace heory
{
namespace tests
{
    void RunTask( Task t, const QString& amidiPortToken );
} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_TASK_RUNNER_H
