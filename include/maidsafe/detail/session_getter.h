/*  Copyright 2014 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_DETAIL_SESSION_GETTER_H_
#define MAIDSAFE_DETAIL_SESSION_GETTER_H_

#include <utility>
#include <vector>

#include "maidsafe/routing/routing_api.h"

#include "maidsafe/nfs/client/data_getter.h"

namespace maidsafe {

typedef std::vector<std::pair<boost::asio::ip::udp::endpoint, asymm::PublicKey>> BootstrapInfo;

namespace detail {

class SessionGetter {
 public:
  explicit SessionGetter(const BootstrapInfo& bootstrap_info);
  nfs_client::DataGetter& data_getter() { return *data_getter_; }

 private:
  void InitRouting(const BootstrapInfo& bootstrap_info);
  routing::Functors InitialiseRoutingCallbacks();
  void OnNetworkStatusChange(int network_health);
  void DoOnNetworkStatusChange(int network_health);

  std::mutex network_health_mutex_;
  std::condition_variable network_health_condition_variable_;
  int network_health_;
  routing::Routing routing_;
  std::unique_ptr<nfs_client::DataGetter> data_getter_;
  nfs::detail::PublicPmidHelper public_pmid_helper_;
  AsioService asio_service_;
};

}  // namespace detail

}  // namespace maidsafe

#endif  // MAIDSAFE_DETAIL_SESSION_GETTER_H_
