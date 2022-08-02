#!/usr/bin/env python
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

# no unicode literals
from __future__ import absolute_import, division, print_function

import sys


log_file_name = sys.argv[1]

# Copy json from stdin to the log file
with open(log_file_name, "a") as f:
    print(f"trigjson.py: Copying STDIN to {log_file_name}")
    json_in = sys.stdin.read()
    print(f"stdin: {json_in}")
    f.write(json_in)
