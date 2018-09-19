// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Phore developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "bignum.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (     0, uint256("0xedee755717c4de66ce52056e36ae0f6e9f0269667fd8a06e3c5367588cbfadbd"));
    
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1532555998, // * UNIX timestamp of last checkpoint block
    943282,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x6bb5bda42ae892d9d73efdb5ee95ac997e1d6621857d3ba1de5200fc99a2fa61"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1504595227,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x6bb5bda42ae892d9d73efdb5ee95ac997e1d6621857d3ba1de5200fc99a2fa61"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1504595227,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x91;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xfd;
        pchMessageStart[3] = 0xea;
        vAlertPubKey = ParseHex("04659d53bd8f7ad9d34a17281febedac754e5a6eb136142d3a9c6c0ea21b6ed7498ceb3d872eed00ae755f7aeadaeb1d9ab5e1a8f1e7efcd0ddcb39d4623c12790");
        nDefaultPort = 19683;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 40; // MonetaryUnit: 1 day
        nTargetSpacing = 1 * 40;  // MonetaryUnit: 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 1000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 468744;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Bitcoin Block #540242: 0x000000000000000000265e9ecd8728c5f24eea700831ca4d74b2c8ea64af0aee";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1536266133;
        genesis.nBits = 0x207fffff;;
        genesis.nNonce = 4;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x388bb718bed848a70552d8a041682100a86253f555ccbd97b95c4af833902ba1"));
            assert(genesis.hashMerkleRoot == uint256("0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071"));
        }
        // Mainnet --- nonce: 4 time: 1536266133 hash: 0x388bb718bed848a70552d8a041682100a86253f555ccbd97b95c4af833902ba1 merklehash: 0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071

        vSeeds.push_back(CDNSSeedData("dns1", "dns1.monetaryunit.org"));
        vSeeds.push_back(CDNSSeedData("dns2", "dns2.monetaryunit.org"));
        vSeeds.push_back(CDNSSeedData("dns3", "dns3.monetaryunit.org"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 76);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 126);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x1F).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "mu";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "042b9747257fcda3363d2ce9de3e23f3397e59c3ca4f3016ec62ef2b7551c49ebc38b9eba2578c3dde9038990cb051ebb465d3dc8eb8214f12d7e6eeecb1fdeb0c";
        strSporkKeyTemp = "0434a01bd58e4c94b2b0238b4511b95e106bd3df6ca3849be89e1ee341c5f86605cb835cfc539f90121b5baee82fb4f04fcdf4c6ad244f9e3be7c10cc0d9a3d38c";
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xbd;
        vAlertPubKey = ParseHex("04d7e13bc896eb07e2db2d7272f5ddfaedfb64b8ed4caa4d917d6e0781b59ca44f8b5d40995622008e40707b47687eebee11cbe3bbaf2348622cc271c7f0d0bd0a");
        nDefaultPort = 19685;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // MonetaryUnit: 1 day
        nTargetSpacing = 1 * 10;  // MonetaryUnit: 1 minute
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;
        nLastPOWBlock = 400;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1505224800;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x593d24a90efc74135f4a2162c71b975dcdb1f0696b2689f4436449aa34749255"));
            assert(genesis.hashMerkleRoot == uint256("0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071"));
        }
        // Testnet --- nonce: 0 time: 1505224800 hash: 0x593d24a90efc74135f4a2162c71b975dcdb1f0696b2689f4436449aa34749255 merklehash: 0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("testnetdns", "testnetdns.monetaryunit.org"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet monetaryunit addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet monetaryunit script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet monetaryunit BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet monetaryunit BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet monetaryunit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tm";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKeyTemp = "049517f3cf92bcd5b1e27f03a9d8de0b979cf46add18d52975e0aa38452c7af6a79c1f9c5ad64ce5ef36900099141030b47d2e871d7f769661473cf81a7ba1491d";
        strSporkKey = "04913cfad775d1ef346697c1caee392d2c3982c1473ed300085a4cf88440c3870574b5d0d063cd87dfd26e610a4db0f1b105fe55866face8863b07971766edfbac";
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xad;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // MonetaryUnit: 1 day
        nTargetSpacing = 1 * 60;        // MonetaryUnit: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1505224800;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nDefaultPort = 19685;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x19c95320506c1a25db643682cb74088713c18449a218c1680c026382b0e99cab"));
            assert(genesis.hashMerkleRoot == uint256("0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071"));
        }
        // Regtestnet --- nonce: 12345 time: 1505224800 hash: 0x19c95320506c1a25db643682cb74088713c18449a218c1680c026382b0e99cab merklehash: 0x4f74c21a149b2ba9771046edb4c441aa6140c579916191ece307697f90ebd071

        if (regenerate)
            exit(0);

        bech32_hrp = "murt";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // {
        //     "PrivateKey": "923EhWh2bJHynX6d4Tqt2Q75bhTDCT1b4kff3qzDKDZHZ6pkQs7",
        //     "PublicKey": "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a"
        // }
        strSporkKey = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
        strSporkKeyTemp = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 19686;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
