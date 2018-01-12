/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "model/converters/pb_common.hpp"
#include "byteutils.hpp"
#include "common/types.hpp"
#include "queries.pb.h"

namespace iroha {
  namespace model {
    namespace converters {

      protocol::Amount serializeAmount(iroha::Amount iroha_amount) {
        protocol::Amount res;
        res.set_precision(iroha_amount.getPrecision());
        auto value = res.mutable_value();
        auto vectorUint64s = iroha_amount.to_uint64s();
        value->set_first(vectorUint64s.at(0));
        value->set_second(vectorUint64s.at(1));
        value->set_third(vectorUint64s.at(2));
        value->set_fourth(vectorUint64s.at(3));
        return res;
      }

      iroha::Amount deserializeAmount(protocol::Amount pb_amount) {
        auto value = pb_amount.value();
        return {value.first(),
                value.second(),
                value.third(),
                value.fourth(),
                static_cast<uint8_t>(pb_amount.precision())};
      }

      protocol::Pager serializePager(const model::Pager &pager) {
        protocol::Pager pb_pager;
        pb_pager.set_tx_hash(pager.tx_hash.to_string());
        pb_pager.set_limit(pager.limit);
        return pb_pager;
      }

      model::Pager deserializePager(const protocol::Pager &pb_pager) {
        model::Pager pager;
        pager.tx_hash = stringToBlob<hash256_t::size()>(pb_pager.tx_hash())
                            .value_or(hash256_t{});
        pager.limit = static_cast<decltype(pager.limit)>(pb_pager.limit());
        return pager;
      }
    }  // namespace converters
  }    // namespace model
}  // namespace iroha
