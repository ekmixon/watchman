#!/usr/bin/env python
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

# no unicode literals
from __future__ import absolute_import, division, print_function

import os


os.environ["PWD"] = os.getcwd()

for k, v in os.environ.items():
    print(f"{k}={v}")
