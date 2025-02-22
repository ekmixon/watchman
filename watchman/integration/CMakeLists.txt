# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

add_fb_python_library(test_support_py
  SOURCES
    Interrupt.py
    TempDir.py
    WatchmanEdenTestCase.py
    WatchmanInstance.py
    WatchmanSCMTestCase.py
    WatchmanTestCase.py
    path_utils.py
  NAMESPACE ""
)

file(GLOB TEST_MODULES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "test_*.py")

# TODO: hook up these tests:
list(REMOVE_ITEM TEST_MODULES
  test_eden_journal.py
  test_eden_pathgen.py
  test_eden_sha1.py
  test_eden_since.py
  test_eden_subscribe.py
  test_eden_unmount.py
  test_eden_watch_root.py
  test_nodejs.py
  test_wm_wait.py
  test_pcre.py
)

add_fb_python_unittest(test_py
  SOURCES
    ${TEST_MODULES}

  DEPENDS
    pywatchman
    test_support_py

  WORKING_DIRECTORY
    ${CMAKE_BINARY_DIR}

  ENV
    "YARN_PATH=${YARN}"
    "NODE_BIN=${NODE}"
    "HGUSER=John Smith <smith@example.com>"
    "NOSCMLOG=1"
    "WATCHMAN_EMPTY_ENV_VAR="
    "WATCHMAN_NO_SPAWN=1"
    "WATCHMAN_BINARY=$<TARGET_FILE:watchman>"
    "WATCHMAN_WAIT_PATH=$<TARGET_PROPERTY:watchman-wait.GEN_PY_EXE,EXECUTABLE>"
    "WATCHMAN_SRC_DIR=${CMAKE_SOURCE_DIR}/watchman"
)
