// Copyright (c) 2019-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H
#define BITCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H

#include "util/system.h"
#include <wallet/scriptpubkeyman.h>

#include <memory>

class ArgsManager;

namespace wallet {
class ExternalSignerScriptPubKeyMan : public DescriptorScriptPubKeyMan
{
  public:
    ExternalSignerScriptPubKeyMan(WalletStorage& storage, WalletDescriptor& descriptor, const ArgsManager& args)
            :   DescriptorScriptPubKeyMan(storage, descriptor, args)
      {}
    ExternalSignerScriptPubKeyMan(WalletStorage& storage, const ArgsManager& args)
            : DescriptorScriptPubKeyMan(storage, args)
      {}

  /** Provide a descriptor at setup time
  * Returns false if already setup or setup fails, true if setup is successful
  */
  bool SetupDescriptor(std::unique_ptr<Descriptor>desc);

  static ExternalSigner GetExternalSigner(const ArgsManager& args);

  bool DisplayAddress(const CScript scriptPubKey, const ExternalSigner &signer) const;

  TransactionError FillPSBT(PartiallySignedTransaction& psbt, const PrecomputedTransactionData& txdata, int sighash_type = 1 /* SIGHASH_ALL */, bool sign = true, bool bip32derivs = false, int* n_signed = nullptr, bool finalize = true) const override;
};
} // namespace wallet
#endif // BITCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H
