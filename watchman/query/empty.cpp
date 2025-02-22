/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "watchman/query/TermRegistry.h"
#include "watchman/watchman_query.h"

#include <memory>

namespace watchman {

class QueryContextBase;

class ExistsExpr : public QueryExpr {
 public:
  EvaluateResult evaluate(QueryContextBase*, FileResult* file) override {
    return file->exists();
  }

  static std::unique_ptr<QueryExpr> parse(Query*, const json_ref&) {
    return std::make_unique<ExistsExpr>();
  }
};
W_TERM_PARSER("exists", ExistsExpr::parse)

class EmptyExpr : public QueryExpr {
 public:
  EvaluateResult evaluate(QueryContextBase*, FileResult* file) override {
    auto exists = file->exists();
    auto stat = file->stat();
    auto size = file->size();

    if (!exists.has_value()) {
      return folly::none;
    }
    if (!exists.value()) {
      return false;
    }

    if (!stat.has_value()) {
      return folly::none;
    }

    if (!size.has_value()) {
      return folly::none;
    }

    if (stat->isDir() || stat->isFile()) {
      return size.value() == 0;
    }

    return false;
  }

  static std::unique_ptr<QueryExpr> parse(Query*, const json_ref&) {
    return std::make_unique<EmptyExpr>();
  }
};
W_TERM_PARSER("empty", EmptyExpr::parse)

} // namespace watchman

/* vim:ts=2:sw=2:et:
 */
