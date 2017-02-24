/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __CORE_REPOSITORY_DOMAIN_ACCOUNT_ASSET_REPOSITORY_HPP__
#define __CORE_REPOSITORY_DOMAIN_ACCOUNT_ASSET_REPOSITORY_HPP__

#include <infra/protobuf/api.pb.h>
#include <memory>
#include <string>
#include <vector>

namespace repository {
namespace account {
std::string add(const std::string &publicKey, const std::string &name,
                const std::vector<std::string> &assets);
bool attach(const std::string &uuid, const std::string &asset);
bool update(const std::string &uuid, const std::vector<std::string> &assets);
bool remove(const std::string &uuid);
Api::Account findByUuid(const std::string &uuid);
bool exists(const std::string &uuid);
}
}
#endif // CORE_REPOSITORY_MERKLETRANSACTIONREPOSITORY_HPP_
