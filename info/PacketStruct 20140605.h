void RequestGetPurchaseBroadcast(ClientNode* Client, BYTE* Body, size_t BodyLen); //20007
void ResponseGetPurchaseBroadcast(ClientNode* Client); //20007
void RequestCheckCommodityOnSale(ClientNode* Client, BYTE* Body, size_t BodyLen); //20006
void ResponseCheckCommodityOnSale(ClientNode* Client); //20006
void RequestBuyCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //20000
void ResponseBuyCommodity(ClientNode* Client); //20000
void RequestBuyCommodityEx(ClientNode* Client, BYTE* Body, size_t BodyLen); //20005
void ResponseBuyCommodityEx(ClientNode* Client); //20005
void RequestGetCommodityList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetCommodityList(ClientNode* Client); //?
void RequestShopCommonBroadcast(ClientNode* Client, BYTE* Body, size_t BodyLen); //20078
void ResponseShopCommonBroadcast(ClientNode* Client); //20078
void RequestSeekFortune(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSeekFortune(ClientNode* Client); //?
void RequestGetCfgFile(ClientNode* Client, BYTE* Body, size_t BodyLen); //20002
void ResponseGetCfgFile(ClientNode* Client); //20002
void RequestGetDiscountCardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20008
void ResponseGetDiscountCardInfo(ClientNode* Client); //20008
void RequestPayRebateCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //20077
void ResponsePayRebateCfg(ClientNode* Client); //20077
void RequestReduceCouponseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20051
void ResponseReduceCouponseInfo(ClientNode* Client); //20051
void RequestGetWorldInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //90
void ResponseGetWorldInfo(ClientNode* Client); //90
void RequestGetChatRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //91
void ResponseGetChatRoomList(ClientNode* Client); //91
void RequestC2FUpLoad(ClientNode* Client, BYTE* Body, size_t BodyLen); //11200
void ResponseC2FUpLoad(ClientNode* Client); //11200
void ResponseEnterRoom(ClientNode* Client); //104
void RequestUseBattleCard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseUseBattleCard(ClientNode* Client); //?
void RequestGetBattleCardLevel(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBattleCardLevel(ClientNode* Client); //?
void RequestGetLottoryCommodityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLottoryCommodityInfo(ClientNode* Client); //?
void RequestRandLottoryCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRandLottoryCommodity(ClientNode* Client); //?
void RequestBuyLottoryCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyLottoryCommodity(ClientNode* Client); //?
void NotifyCrashModeBeginRoll(ClientNode* Client); //?
void NotifyCrashModeEndRoll(ClientNode* Client); //?
void RequestCrashModeRollAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCrashModeRollAward(ClientNode* Client); //?
void RequestC2GGetPlayerLoverMatchInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetPlayerLoverMatchInfo(ClientNode* Client); //11310
void RequestC2GInviteTeamMate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GInviteTeamMate(ClientNode* Client); //11312
void NotifyG2CInviteTeamMateResult(ClientNode* Client); //11313
void NotifyG2CBeInviteTeamMate(ClientNode* Client); //11314
void AckG2CBeInviteTeamMate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyG2CTimeOutAckBeInviteTeamMate(ClientNode* Client); //11315
void NotifyG2CAllocLoveMatchServer(ClientNode* Client); //11319
void RequestC2GMatchTeamMate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMatchTeamMate(ClientNode* Client); //11316
void NotifyG2CMatchTeamMateResult(ClientNode* Client); //11317
void RequestC2GCancelMatchTeamMate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetLoverMatchInviteList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLoverMatchInviteList(ClientNode* Client); //11320
void RequestC2LMEnterLoveMatchServer(ClientNode* Client, BYTE* Body, size_t BodyLen); //11326
void ResponseC2LMEnterLoveMatchServer(ClientNode* Client); //11326
void RequestC2LMMatchRival(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2LMMatchRival(ClientNode* Client); //11327
void NotifyLM2CMatchRival(ClientNode* Client); //11328
void RequestC2LMCancelMatchRival(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2LMCancelMatchRival(ClientNode* Client); //11329
void NotifyLM2CCancelMatchRival(ClientNode* Client); //11330
void NotifyLM2CMatchRivalResult(ClientNode* Client); //11331
void NotifyLM2CLoveMatchPlayerInfo(ClientNode* Client); //11332
void NotifyLM2CCooperInc(ClientNode* Client); //11338
void RequestC2LMTriggerSuperJet(ClientNode* Client, BYTE* Body, size_t BodyLen); //11339
void ResponseC2LMTriggerSuperJet(ClientNode* Client); //11339
void NotifyLM2CSuperJet(ClientNode* Client); //11340
void NotifyLM2CLoveTime(ClientNode* Client); //11341
void RequestC2LMOverSuperJet(ClientNode* Client, BYTE* Body, size_t BodyLen); //11342
void NotifyLM2CLoveMatchRaceOver(ClientNode* Client); //11333
void RequestC2LMReturnLoveMatchRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11334
void ResponseC2LMReturnLoveMatchRoom(ClientNode* Client); //11334
void NotifyLM2CReturnLoveMatchRoom(ClientNode* Client); //11335
void RequestC2LMQuitLoveMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //11336
void ResponseC2LMQuitLoveMatch(ClientNode* Client); //11336
void RequestC2GLoveMatchLottery(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GLoveMatchLottery(ClientNode* Client); //11337
void RequestC2GGetLoveMatchLotteryBroad(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetLoveMatchLotteryBroad(ClientNode* Client); //11343
void RequestC2GGetLoverMatchCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetLoverMatchCfg(ClientNode* Client); //11311
void RequestQueryIsInLoverMatchTime(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQueryIsInLoverMatchTime(ClientNode* Client); //11321
void RequestGetAuctionCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetAuctionCfg(ClientNode* Client); //11411
void RequestGetCurAuctionInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetCurAuctionInfo(ClientNode* Client); //11413
void RequestGetParticipateAuction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetParticipateAuction(ClientNode* Client); //11412
void RequestGetAuctionList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetAuctionList(ClientNode* Client); //11414
void RequestBidAuctionCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBidAuctionCommodity(ClientNode* Client); //11415
void NotifyClientBidExceedByOther(ClientNode* Client); //11416
void NotifyClientSucessAuction(ClientNode* Client); //11417
void RequestPayAuctionCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePayAuctionCommodity(ClientNode* Client); //11418
void RequestGetSingleAuctionInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSingleAuctionInfo(ClientNode* Client); //11419
void NotifyLockedAuctionMoney(ClientNode* Client); //11420
void NotifyAuctionEnd(ClientNode* Client); //11446
void RequestFBChangeLev(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFBChangeLev(ClientNode* Client); //11360
void NotifyFBChangeLev(ClientNode* Client); //11361
void NotifyBroadcast(ClientNode* Client); //541
void RequestOpenBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //168
void RequestSelOptBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //616
void ResponseSelOptBoxAward(ClientNode* Client); //616
void NotifySelOptBoxAward(ClientNode* Client); //617
void RequestGetShortCutSet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetShortCutSet(ClientNode* Client); //11356
void RequestSetShortCutSet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSetShortCutSet(ClientNode* Client); //11357
void RequestGetConsumeScoreConfUrl(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetConsumeScoreConfUrl(ClientNode* Client); //11471
void RequestConsumeScoreExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseConsumeScoreExchange(ClientNode* Client); //11472
void NotifyG2CWizardSimpleInfo(ClientNode* Client); //11473
void RequestGetWizardHomeBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWizardHomeBaseInfo(ClientNode* Client); //11474
void RequestLogoutWizardHome(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLogoutWizardHome(ClientNode* Client); //11519
void RequestCollegeUpgradeWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCollegeUpgradeWizard(ClientNode* Client); //11476
void NotifyCollegeUpgradeResultWizard(ClientNode* Client); //11515
void RequestSkillStrengthenWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkillStrengthenWizard(ClientNode* Client); //11477
void RequestSkillStudyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkillStudyWizard(ClientNode* Client); //11478
void RequestSkillForgetWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkillForgetWizard(ClientNode* Client); //11479
void RequestCollegeUpgradeImmediatelyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCollegeUpgradeImmediatelyWizard(ClientNode* Client); //11481
void RequestWorkShopUpgradeWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWorkShopUpgradeWizard(ClientNode* Client); //11484
void NotifyWorkShopUpgradeResultWizard(ClientNode* Client); //11516
void RequestWorkShopUpgradeImmediatelyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWorkShopUpgradeImmediatelyWizard(ClientNode* Client); //11485
void RequestJobWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseJobWizard(ClientNode* Client); //11486
void NotifyJobResult(ClientNode* Client); //11517
void RequestCancelJobWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelJobWizard(ClientNode* Client); //11487
void RequestJobImmediatelyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseJobImmediatelyWizard(ClientNode* Client); //11488
void RequestReceiveJobAwardWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveJobAwardWizard(ClientNode* Client); //11489
void RequestAdventureWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAdventureWizard(ClientNode* Client); //11491
void RequestCancelAdventureWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelAdventureWizard(ClientNode* Client); //11492
void RequestAdventureImmediatelyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAdventureImmediatelyWizard(ClientNode* Client); //11493
void RequestReceiveAdventureAwardWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveAdventureAwardWizard(ClientNode* Client); //11510
void NotifyAdventureResult(ClientNode* Client); //11518
void RequestGetWizardFriendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWizardFriendList(ClientNode* Client); //11494
void RequestChallengeWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChallengeWizard(ClientNode* Client); //11495
void RequestFarmUpgradeWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFarmUpgradeWizard(ClientNode* Client); //11496
void RequestFarmUpgradeImmediatelyWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFarmUpgradeImmediatelyWizard(ClientNode* Client); //11497
void NotifyFarmUpgradeResultWizard(ClientNode* Client); //11524
void RequestWakeWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWakeWizard(ClientNode* Client); //11502
void RequestCareWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCareWizard(ClientNode* Client); //11499
void RequestFeedWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFeedWizard(ClientNode* Client); //11500
void RequestGetFriendWizardBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFriendWizardBaseInfo(ClientNode* Client); //11501
void RequestReleaseWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReleaseWizard(ClientNode* Client); //11503
void RequestSetWizardVisible(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSetWizardVisible(ClientNode* Client); //11504
void RequestEvoluteWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseEvoluteWizard(ClientNode* Client); //11505
void RequestCliffordWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCliffordWizard(ClientNode* Client); //11511
void RequestWateringOneselfWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWateringOneselfWizard(ClientNode* Client); //11512
void RequestWateringFriendWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWateringFriendWizard(ClientNode* Client); //11513
void RequestReceiveLuckyFruitAwardWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveLuckyFruitAwardWizard(ClientNode* Client); //11514
void RequestModifyWizardNickname(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseModifyWizardNickname(ClientNode* Client); //11498
void NotifyG2CBeWateredWizard(ClientNode* Client); //11521
void RequestGetOtherWizardHomeBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetOtherWizardHomeBaseInfo(ClientNode* Client); //11522
void RequestGetWizardRecommendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWizardRecommendList(ClientNode* Client); //11523
void RequestGetWizardEvolutionHistoryInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWizardEvolutionHistoryInfo(ClientNode* Client); //11525
void RequestChangeCarryWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeCarryWizard(ClientNode* Client); //11506
void RequestHuanHuaWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseHuanHuaWizard(ClientNode* Client); //11507
void RequestCancelHuanHuaWizard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelHuanHuaWizard(ClientNode* Client); //11508
void NotifyG2CChangeHuanHuaWizard(ClientNode* Client); //11509
void NotifyG2CChangeCarryWizard(ClientNode* Client); //11490
void RequestC2GGetWizardBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetWizardBaseInfo(ClientNode* Client); //11526
void RequestGetWizardHomeCommodityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWizardHomeCommodityInfo(ClientNode* Client); //11527
void RequestRandWizardHomeCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRandWizardHomeCommodity(ClientNode* Client); //11528
void RequestBuyWizardHomeCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsetBuyWizardHomeCommodity(ClientNode* Client); //11529
void RequestC2GGetWizardActivityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetWizardActivityInfo(ClientNode* Client); //11482
void RequestSetWizardHomeDressInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSetWizardHomeDressInfo(ClientNode* Client); //11530
void NotifyG2CCreateNewWizard(ClientNode* Client); //11520
void RequestGetAdventureDisplayInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetAdventureDisplayInfo(ClientNode* Client); //11531
void RequestNewGetFriendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //163
void ResponseNewGetFriendList(ClientNode* Client); //163
void RequestC2GGetSignInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetSignInfo(ClientNode* Client); //233
void RequestC2GSign(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GSign(ClientNode* Client); //234
void RequestC2GGetSignAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetSignAward(ClientNode* Client); //235
void NotifyG2CUpdateSignInfo(ClientNode* Client); //236
void RequestC2GMagicCardGetNews(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMagicCardGetNews(ClientNode* Client); //12000
void NotifyC2GMagicCardNotifyCardsEverHad(ClientNode* Client); //12001
void RequestC2GMagicCardGetExchangeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMagicCardGetExchangeInfo(ClientNode* Client); //12002
void RequestC2GMagicCardCompound(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMagicCardCompound(ClientNode* Client); //12003
void RequestC2GMagicCardExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMagicCardExchange(ClientNode* Client); //12004
void RequestC2GMagicCardTransform(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GMagicCardTransform(ClientNode* Client); //12005
void NotifyC2GMagicCardNotifyGenCardAward(ClientNode* Client); //12006
void RequestG2DMagicCardGetCardAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseG2DMagicCardGetCardAward(ClientNode* Client); //12007
void RequestC2GSandglassInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GSandglassInfo(ClientNode* Client); //237
void RequestC2GStartSandglass(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GStartSandglass(ClientNode* Client); //238
void RequestC2GGetSandglassExp(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetSandglassExp(ClientNode* Client); //239
void NotifyG2CSandglassExpReady(ClientNode* Client); //240
void RequestC2GGetPlayerFizzStarBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetPlayerFizzStarBaseInfo(ClientNode* Client); //11591
void NotifyG2CFizzStarCfg(ClientNode* Client); //11595
void RequestC2GGetFizzStarActivityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GFizzStarActivityInfo(ClientNode* Client); //11596
void NotifyG2CAddFizzStarActivityInfo(ClientNode* Client); //11600
void RequestC2GGetFizzStarFriendInfoList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetFizzStarFriendInfoList(ClientNode* Client); //11597
void RequestC2GGetFizzStarTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetFizzStarTask(ClientNode* Client); //11592
void RequestC2GDonateFriendFizzSource(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GDonateFriendFizzSource(ClientNode* Client); //11593
void NotifyG2CFizzSourceAddition(ClientNode* Client); //11594
void NotifyG2CUpdateSkateTaskLevel(ClientNode* Client); //778
void RequestSkateSkillUpgrade(ClientNode* Client, BYTE* Body, size_t BodyLen); //10927
void ResponseSkateSkillUpgrade(ClientNode* Client); //10927
void NotifyG2CSkateCfg(ClientNode* Client); //10928
void RequestC2GFizzStarLottery(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GFizzStarLottery(ClientNode* Client); //11599
void RequestC2GGetFizzStarRecommendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetFizzStarRecommendList(ClientNode* Client); //11601
void NotifyG2CFizzStarSpecialTaskAward(ClientNode* Client); //11602
void RequestReceiveGuildVipGift(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveGuildVipGift(ClientNode* Client); //12032
void RequestGetGVLottoryCommodityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGVLottoryCommodityInfo(ClientNode* Client); //12037
void RequestRandGVLottoryCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRandGVLottoryCommodity(ClientNode* Client); //12038
void RequestBuyGVLottoryCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyGVLottoryCommodity(ClientNode* Client); //12039
void RequestPopularity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePopularity(ClientNode* Client); //1700
void RequestGetLadderMatchInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchInfo(ClientNode* Client); //?
void RequestGetLadderMatchRecord(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchRecord(ClientNode* Client); //?
void RequestParticipateLadderMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseParticipateLadderMatch(ClientNode* Client); //?
void RequestCancelParticipateLadderMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelParticipateLadderMatch(ClientNode* Client); //?
void NotifyPlayerParticipateLadderMatchReady(ClientNode* Client); //?
void NotifyPlayerParticipateLadderMatchTimeout(ClientNode* Client); //?
void NotifyPlayerLadderMatchBeginCountDown(ClientNode* Client); //?
void RequestGetLadderMatchPlayerToplist(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchPlayerToplist(ClientNode* Client); //?
void RequestGetLadderMatchGuildToplist(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchGuildToplist(ClientNode* Client); //?
void RequestReceiveLadderMatchAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveLadderMatchAward(ClientNode* Client); //?
void NotifyPlayerLadderMatchAward(ClientNode* Client); //?
void RequestGetLadderMatchAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchAwardCfg(ClientNode* Client); //?
void RequestGetLadderMatchAchieveList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLadderMatchAchieveList(ClientNode* Client); //?
void RequestQueryLadderMatchAchieveAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQueryLadderMatchAchieveAwardCfg(ClientNode* Client); //?
void NotifyDeductLadderMatchScore(ClientNode* Client); //13059
void NotifyForbiddenMode(ClientNode* Client); //13063
void NotifyMatchLiveInfo(ClientNode* Client); //242
void RequestWishTreeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestWishTreeWater(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestWishTreeBuyCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifySGS2CWlActivityStatus(ClientNode* Client); //13101
void RequestC2GActivityDetailInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifySGS2CWlActivityInfo(ClientNode* Client); //13102
void ResponseC2GActivityDetailInfo(ClientNode* Client); //13103
void NotifyPlayerInActivity(ClientNode* Client); //13104
void NotifyWL2CHorseLight(ClientNode* Client); //13105
void NotifyWlLoginTips(ClientNode* Client); //995
void RequestBroadCastWlQTRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBroadCastWlQTRoom(ClientNode* Client); //996
void RequestMatchingGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMatchingGame(ClientNode* Client); //13110
void RequestCancelMatchingGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelMatchingGame(ClientNode* Client); //13111
void NotifyPlayerMatchingGameResult(ClientNode* Client); //13112
void NotifyClientUpdateGuildVipInfo(ClientNode* Client); //12031
void RequestRandomOneNobleID(ClientNode* Client, BYTE* Body, size_t BodyLen); //1652
void ResponseRandomOneNobleID(ClientNode* Client); //1652
void RequestDropRandomNobleID(ClientNode* Client, BYTE* Body, size_t BodyLen); //1653
void RequestReplaceNobleID(ClientNode* Client, BYTE* Body, size_t BodyLen); //1654
void ResponseReplaceNobleID(ClientNode* Client); //1654
void RequestRegister(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestRegister2(ClientNode* Client, BYTE* Body, size_t BodyLen); //357
void ResponseRegister(ClientNode* Client); //129
void RequestLogin(ClientNode* Client, BYTE* Body, size_t BodyLen); //100
void ResponseLogin(ClientNode* Client); //82
void NotifyMaxItemNumExtended(ClientNode* Client); //11475
void NotifyLoginMoreInfo(ClientNode* Client); //223
void RequestLogout(ClientNode* Client, BYTE* Body, size_t BodyLen); //101
void ResponseLogout(ClientNode* Client); //101
void RequestGetRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //102
void NotifyClientUpdateGuildScoreInRoomInfo(ClientNode* Client); //12033
void ResponseGetRoomList(ClientNode* Client); //102
void RequestCreateRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //103
void ResponseCreateRoom(ClientNode* Client); //103
void RequestEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //104
void NotifyEnterRoomMoreInfo(ClientNode* Client); //224
void NotifyEnterRoom(ClientNode* Client); //500
void RequestLeaveRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //105
void ResponseLeaveRoom(ClientNode* Client); //105
void NotifyLeaveRoom(ClientNode* Client); //501
void NotifyChangeRoomOwner(ClientNode* Client); //524
void RequestChangeTeam(ClientNode* Client, BYTE* Body, size_t BodyLen); //128
void ResponseChangeTeam(ClientNode* Client); //128
void NotifyPlayerChangeTeam(ClientNode* Client); //523
void RequestTransferUDPOK(ClientNode* Client, BYTE* Body, size_t BodyLen); //499
void ResponseTransferUDPOK(ClientNode* Client); //499
void NotifyUDPOK(ClientNode* Client); //999
void RequestQuickEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //106
void ResponseQuickEnterRoom(ClientNode* Client); //106
void NotifyQuickEnterRoomMoreInfo(ClientNode* Client); //225
void RequestChangeSeatState(ClientNode* Client, BYTE* Body, size_t BodyLen); //107
void ResponseChangeSeatState(ClientNode* Client); //107
void NotifyChangeSeatState(ClientNode* Client); //502
void RequestKickFromRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //108
void ResponseKickFromRoom(ClientNode* Client); //108
void NotifyKickFromRoom(ClientNode* Client); //503
void NotifyUnLockMap(ClientNode* Client); //821
void RequestChangeReadyState(ClientNode* Client, BYTE* Body, size_t BodyLen); //109
void ResponseChangeReadyState(ClientNode* Client); //109
void NotifyChangeReadyState(ClientNode* Client); //504
void RequestStartGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //110
void ResponseStartGame(ClientNode* Client); //110
void RequestTalk(ClientNode* Client, BYTE* Body, size_t BodyLen); //111
void ResponseTalk(ClientNode* Client); //111
void NotifyTalk(ClientNode* Client); //505
void RequestHello(ClientNode* Client, BYTE* Body, size_t BodyLen); //112
void ResponseHello(ClientNode* Client); //112
void NotifyTestNetSpeed(ClientNode* Client); //506
void AckTestNetSpeed(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyKickFromServer(ClientNode* Client); //900
void RequestGetFriendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFriendList(ClientNode* Client); //?
void RequestGetGroupFriendBaseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //148
void ResponseGetGroupFriendBaseInfo(ClientNode* Client); //148
void RequestModifyPlayerSignature(ClientNode* Client, BYTE* Body, size_t BodyLen); //376
void ResponseModifyPlayerSignature(ClientNode* Client); //376
void RequestAddFriend(ClientNode* Client, BYTE* Body, size_t BodyLen); //114
void ResponseAddFriend(ClientNode* Client); //114
void RequestDeleteFriend(ClientNode* Client, BYTE* Body, size_t BodyLen); //115
void ResponseDeleteFriend(ClientNode* Client); //115
void RequestAddFriendGroup(ClientNode* Client, BYTE* Body, size_t BodyLen); //116
void ResponseAddFriendGroup(ClientNode* Client); //116
void RequestDeleteFriendGroup(ClientNode* Client, BYTE* Body, size_t BodyLen); //117
void ResponseDeleteFriendGroup(ClientNode* Client); //117
void RequestChangeFriendGroupName(ClientNode* Client, BYTE* Body, size_t BodyLen); //149
void ResponseChangeFriendGroupName(ClientNode* Client); //149
void RequestMoveFriendToSomeGroup(ClientNode* Client, BYTE* Body, size_t BodyLen); //118
void ResponseMoveFriendToSomeGroup(ClientNode* Client); //118
void NotifyBeAddedAsFriend(ClientNode* Client); //507
void AckBeAddedAsFriend(ClientNode* Client, BYTE* Body, size_t BodyLen); //507
void NotifyAddFriendResult(ClientNode* Client); //508
void NotifyBeDeletedByFriend(ClientNode* Client); //553
void NotifyGameBegin(ClientNode* Client); //509
void NotifyCheckPointTimeDiff(ClientNode* Client); //274
void RequestPrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen); //120
void NotifyWaitUnReadyPlayers(ClientNode* Client); //510
void NotifyRaceBegin(ClientNode* Client); //511
void NotifyCountDown(ClientNode* Client); //512
void NotifyRaceOver(ClientNode* Client); //513
void NotifyRaceShow(ClientNode* Client); //515
void NotifyGameOver(ClientNode* Client); //514
void RequestReportCurrentInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //123
void RequestFindPlayerByQQ(ClientNode* Client, BYTE* Body, size_t BodyLen); //122
void ResponseFindPlayerByQQ(ClientNode* Client); //122
void RequestGetProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //124
void ResponseGetProp(ClientNode* Client); //124
void NotifyDraftAward(ClientNode* Client); //582
void NotifyGetProp(ClientNode* Client); //516
void RequestUseProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //125
void ResponseUseProp(ClientNode* Client); //125
void NotifyUseProp(ClientNode* Client); //517
void RequestPropEffectResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //126
void NotifyPropEffectResult(ClientNode* Client); //518
void RequestChangeAimState(ClientNode* Client, BYTE* Body, size_t BodyLen); //127
void NotifyChangeAimState(ClientNode* Client); //519
void RequestReportDrift(ClientNode* Client, BYTE* Body, size_t BodyLen); //119
void ResponseReportDrift(ClientNode* Client); //119
void NotifyReportDrift(ClientNode* Client); //521
void RequestChangeMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //121
void ResponseChangeMap(ClientNode* Client); //121
void NotifyChangeMap(ClientNode* Client); //520
void NotifyPlayerFinishRace(ClientNode* Client); //522
void NotifyReplaceProp(ClientNode* Client); //525
void NotifyAddProp(ClientNode* Client); //526
void NotifyClientUpdateMoney(ClientNode* Client); //528
void NotifyClientAddItem(ClientNode* Client); //529
void NotifyClientUpdateMoneyExp(ClientNode* Client); //559
void RequestChangeItemStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //130
void ResponseChangeItemStatus(ClientNode* Client); //130
void NotifyChangeItemStatus(ClientNode* Client); //527
void NotifyChangeCarBattleModeSkillInfoList(ClientNode* Client); //11675
void RequestCheckName(ClientNode* Client, BYTE* Body, size_t BodyLen); //133
void ResponseCheckName(ClientNode* Client); //133
void NotifySingleGameBegin(ClientNode* Client); //530
void NotifySingleRaceBegin(ClientNode* Client); //531
void NotifySingleRaceFinish(ClientNode* Client); //532
void NotifySingleRaceOver(ClientNode* Client); //533
void NotifySingleGameOver(ClientNode* Client); //534
void NotifyTaskProgressRate(ClientNode* Client); //536
void NotifyTaskAward(ClientNode* Client); //537
void RequestStartSingleTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //138
void ResponseStartSingleTask(ClientNode* Client); //138
void RequestReportCurrentOpt(ClientNode* Client, BYTE* Body, size_t BodyLen); //139
void ResponseReportCurrentOpt(ClientNode* Client); //139
void RequestGetTaskList(ClientNode* Client, BYTE* Body, size_t BodyLen); //135
void ResponseGetTaskList(ClientNode* Client); //135
void RequestTakeTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //136
void ResponseTakeTask(ClientNode* Client); //136
void RequestDeleteTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //137
void ResponseDeleteTask(ClientNode* Client); //137
void RequestSkipTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //140
void ResponseSkipTask(ClientNode* Client); //140
void RequestSkipFreshTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //183
void ResponseSkipFreshTask(ClientNode* Client); //183
void NotifyAntiBot(ClientNode* Client); //538
void AckAntiBot(ClientNode* Client, BYTE* Body, size_t BodyLen); //538
void AckDpData(ClientNode* Client, BYTE* Body, size_t BodyLen); //562
void RequestGMKickOff(ClientNode* Client, BYTE* Body, size_t BodyLen); //141
void ResponseGMKickOff(ClientNode* Client); //141
void NotifyGMKickOff(ClientNode* Client); //539
void RequestGMForbidden(ClientNode* Client, BYTE* Body, size_t BodyLen); //142
void ResponseGMForbidden(ClientNode* Client); //142
void NotifyGMForbidden(ClientNode* Client); //540
void NotifyAcquaintanceLogin(ClientNode* Client); //599
void NotifyAdvertisement(ClientNode* Client); //549
void NotifyUpdateExperience(ClientNode* Client); //546
void RequestGetLicenseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //145
void ResponseGetLicenseInfo(ClientNode* Client); //145
void NotifyUpdateLicense(ClientNode* Client); //547
void NotifyAddLicenseInfo(ClientNode* Client); //552
void NotifyWordList(ClientNode* Client); //554
void RequestDeleteWord(ClientNode* Client, BYTE* Body, size_t BodyLen); //150
void ResponseDeleteWord(ClientNode* Client); //150
void RequestSwitchInterface(ClientNode* Client, BYTE* Body, size_t BodyLen); //151
void ResponseSwitchInterface(ClientNode* Client); //?
void RequestGetSystemTaskList(ClientNode* Client, BYTE* Body, size_t BodyLen); //152
void ResponseGetSystemTaskList(ClientNode* Client); //152
void NotifyAddTaskInfo(ClientNode* Client); //557
void NotifyActivityAward(ClientNode* Client); //558
void NotifyKartPhysParam(ClientNode* Client); //?
void NotifyBugletTalk(ClientNode* Client); //555
void NotifyUseItemResult(ClientNode* Client); //556
void RequestUseItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //158
void ResponseUseItem(ClientNode* Client); //158
void NotifyUseItem(ClientNode* Client); //567
void RequestInvitePlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //159
void ResponseInvitePlayer(ClientNode* Client); //159
void NotifyInviteResult(ClientNode* Client); //568
void NotifyBeInvited(ClientNode* Client); //569
void AckBeInvited(ClientNode* Client, BYTE* Body, size_t BodyLen); //569
void RequestExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //160
void ResponseExchange(ClientNode* Client); //160
void RequestNPCComplete(ClientNode* Client, BYTE* Body, size_t BodyLen); //161
void RequestChangeGender(ClientNode* Client, BYTE* Body, size_t BodyLen); //162
void ResponseChangeGender(ClientNode* Client); //162
void NotifyItemInvalid(ClientNode* Client); //570
void NotifyFriendDegree(ClientNode* Client); //571
void RequestStartTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //164
void ResponseStartTask(ClientNode* Client); //164
void RequestUseProp2(ClientNode* Client, BYTE* Body, size_t BodyLen); //165
void RequestEngage(ClientNode* Client, BYTE* Body, size_t BodyLen); //166
void ResponseEngage(ClientNode* Client); //166
void NotifyBeEngaged(ClientNode* Client); //572
void AckBeEngaged(ClientNode* Client, BYTE* Body, size_t BodyLen); //572
void NotifyEngageResult(ClientNode* Client); //573
void RequestCancelEngage(ClientNode* Client, BYTE* Body, size_t BodyLen); //167
void ResponseCancelEngage(ClientNode* Client); //167
void NotifyCancelEngage(ClientNode* Client); //574
void NotifyModifyHoneyNickName(ClientNode* Client); //576
void NotifyDeleteItem(ClientNode* Client); //577
void NotifyGetLottery(ClientNode* Client); //578
void RequestGetKeyOfBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //189
void ResponseGetKeyOfBox(ClientNode* Client); //189
void RequestGetBoxItems(ClientNode* Client, BYTE* Body, size_t BodyLen); //190
void ResponseGetBoxItems(ClientNode* Client); //190
void ResponseOpenBox(ClientNode* Client); //168
void RequestOutDoorEggInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //169
void ResponseOutDoorEggInfo(ClientNode* Client); //169
void RequestOutDoorSmashEgg(ClientNode* Client, BYTE* Body, size_t BodyLen); //170
void ResponseOutDoorSmashEgg(ClientNode* Client); //170
void NotifyOutDoorSmashEgg(ClientNode* Client); //579
void NotifyOutDoorEggInfo(ClientNode* Client); //580
void NotifyBorderGameCondition(ClientNode* Client); //544
void RequestEnterBorderGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //143
void ResponseEnterBorderGame(ClientNode* Client); //143
void NotifyMatchFailed(ClientNode* Client); //545
void RequestCancelBorderMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //147
void ResponseCancelborderMatch(ClientNode* Client); //147
void NotifyPlayerLeaveBorderGame(ClientNode* Client); //550
void NotifyBorderRaceOver(ClientNode* Client); //542
void NotifyHero(ClientNode* Client); //543
void RequestCheatingReport(ClientNode* Client, BYTE* Body, size_t BodyLen); //581
void RequestGetNationHonorList(ClientNode* Client, BYTE* Body, size_t BodyLen); //144
void ResponseGetNationHonorList(ClientNode* Client); //144
void NotifyBorderPlayerInfo(ClientNode* Client); //548
void RequestCountryHonor(ClientNode* Client, BYTE* Body, size_t BodyLen); //146
void ResponseCountryHonor(ClientNode* Client); //146
void RequestEnterOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen); //352
void ResponseEnterOutdoor(ClientNode* Client); //352
void NotifyEnterOutdoor(ClientNode* Client); //852
void RequestChangeHammerStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //359
void ResponseChangeHammerStatus(ClientNode* Client); //359
void NotifyChangeHammerStatus(ClientNode* Client); //861
void RequestLeaveOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen); //353
void ResponseLeaveOutdoor(ClientNode* Client); //353
void NotifyLeaveOutdoor(ClientNode* Client); //853
void RequestExchangeLoverMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //301
void NotifyRequestExchangeLoverMode(ClientNode* Client); //302
void ResponseExchangeLoverMode(ClientNode* Client); //303
void NotifyExchangeLoverMode(ClientNode* Client); //304
void RequestHeroPos(ClientNode* Client, BYTE* Body, size_t BodyLen); //350
void NotifySynAllHeroPos(ClientNode* Client); //850
void RequestHeroMove(ClientNode* Client, BYTE* Body, size_t BodyLen); //351
void NotifyHeroMove(ClientNode* Client); //851
void NotifyHeroLevelup(ClientNode* Client); //854
void NotifyRelaxSystemMsg(ClientNode* Client); //860
void RequestHeroDoAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //355
void ResponseHeroDoAction(ClientNode* Client); //355
void NotifyHeroDoAction(ClientNode* Client); //855
void RequestKartPetDoAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //348
void NotifyKartPetDoAction(ClientNode* Client); //349
void NotifyPlayerDoAction(ClientNode* Client); //856
void RequestChangeIdentity(ClientNode* Client, BYTE* Body, size_t BodyLen); //131
void ResponseChangeIdentity(ClientNode* Client); //131
void RequestTransferByTCP(ClientNode* Client, BYTE* Body, size_t BodyLen); //153
void NotifyTranferByTCP(ClientNode* Client); //560
void RequestModifyNickname(ClientNode* Client, BYTE* Body, size_t BodyLen); //154
void ResponseModifyNickname(ClientNode* Client); //154
void NotifyBeginModifyNickname(ClientNode* Client); //561
void RequestUseHammer(ClientNode* Client, BYTE* Body, size_t BodyLen); //358
void ResponseUseHammer(ClientNode* Client); //358
void NotifyMatchInfo(ClientNode* Client); //563
void RequestEnterMatchGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //155
void ResponseEnterMatchGame(ClientNode* Client); //155
void NotifyMatchRaceOver(ClientNode* Client); //564
void NotifyMatchPlayerInfo(ClientNode* Client); //565
void RequestCancelMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //156
void ResponseCancelMatch(ClientNode* Client); //156
void NotifyPlayerLeaveMatchGame(ClientNode* Client); //566
void RequestClearPoint(ClientNode* Client, BYTE* Body, size_t BodyLen); //157
void ResponseClearPoint(ClientNode* Client); //157
void RequestGetNumericalValue(ClientNode* Client, BYTE* Body, size_t BodyLen); //920
void NotifyNumericalValue(ClientNode* Client); //921
void RequestGetWlMatchAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //962
void ResponseGetWlMatchAwardCfg(ClientNode* Client); //962
void RequestGetWlMatchAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //963
void ResponseGetWlMatchAward(ClientNode* Client); //963
void RequestEnterWlMatchGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //964
void ResponseEnterWlMatchGame(ClientNode* Client); //964
void NotifyEnterWlMatchGameFailed(ClientNode* Client); //965
void RequestCancelWlMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //970
void ResponseCancelWlMatch(ClientNode* Client); //970
void NotifyWlMatchPlayerInfo(ClientNode* Client); //971
void NotifyPlayerLeaveWlMatchGame(ClientNode* Client); //973
void RequestQueryWlMatchStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //976
void ResponseQueryWlMatchStatus(ClientNode* Client); //976
void NotifyBriefGuildInfo(ClientNode* Client); //15205
void RequestCreateGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15000
void ResponseCreateGuild(ClientNode* Client); //15000
void RequestAddMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //15001
void ResponseAddMember(ClientNode* Client); //15001
void NotifyBeAddedToGuild(ClientNode* Client); //15206
void RequestReplyBeAddedToGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15014
void NotifyAddToGuildResult(ClientNode* Client); //15210
void RequestApplyJoinGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15010
void ResponseApplyJoinGuild(ClientNode* Client); //15010
void NotifyApplyJoinGuild(ClientNode* Client); //15208
void RequestReplyJoinGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15013
void RequestRemoveMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //15002
void ResponseRemoveMember(ClientNode* Client); //15002
void NotifyRemoveMember(ClientNode* Client); //15202
void RequestGetGuildList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15004
void ResponseGetGuildList(ClientNode* Client); //15004
void RequestFindGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15009
void ResponseFindGuild(ClientNode* Client); //15009
void RequestGuildDetail(ClientNode* Client, BYTE* Body, size_t BodyLen); //15003
void ResponseGuildDetail(ClientNode* Client); //15003
void RequestChangeMemberDuty(ClientNode* Client, BYTE* Body, size_t BodyLen); //15006
void ResponseChangeMemberDuty(ClientNode* Client); //15006
void NotifyChangeMemberDutyResult(ClientNode* Client); //15204
void RequestModifyDutyRight(ClientNode* Client, BYTE* Body, size_t BodyLen); //15007
void ResponseModifyDutyRight(ClientNode* Client); //15007
void RequestModifyGuildAttriute(ClientNode* Client, BYTE* Body, size_t BodyLen); //15008
void ResponseModifyGuildAttriute(ClientNode* Client); //15008
void RequestModifyGuildNotes(ClientNode* Client, BYTE* Body, size_t BodyLen); //15011
void ResponseModifyGuildNotes(ClientNode* Client); //15011
void RequestModifyGuildDesc(ClientNode* Client, BYTE* Body, size_t BodyLen); //15012
void ResponseModifyGuildDesc(ClientNode* Client); //15012
void RequestPlayerGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //15015
void ResponsePlayerGuildInfo(ClientNode* Client); //15015
void RequestGuildLogInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //15016
void ResponseGuildLogInfo(ClientNode* Client); //15016
void RequestCheckGuildName(ClientNode* Client, BYTE* Body, size_t BodyLen); //15017
void ResponseCheckGuildName(ClientNode* Client); //15017
void NotifyDismissGuildResult(ClientNode* Client); //15217
void RequestSavingQQshow(ClientNode* Client, BYTE* Body, size_t BodyLen); //356
void ResponseSavingQQshow(ClientNode* Client); //356
void NotifyLoginMsg(ClientNode* Client); //575
void RequestRefitKart(ClientNode* Client, BYTE* Body, size_t BodyLen); //174
void ResponseRefitKart(ClientNode* Client); //174
void RequestGetForbidRefitKartList(ClientNode* Client, BYTE* Body, size_t BodyLen); //175
void ResponseGetForbidRefitKartList(ClientNode* Client); //175
void NotifyUpdatePetExp(ClientNode* Client); //583
void NotifyPetEvolution(ClientNode* Client); //584
void NotifyUpdatePetPL(ClientNode* Client); //585
void NotifyAddPet(ClientNode* Client); //586
void RequestResetPL(ClientNode* Client, BYTE* Body, size_t BodyLen); //176
void NotifyBroadcastPetEvolution(ClientNode* Client); //587
void NotifyBroadcastPetLevelUp(ClientNode* Client); //589
void NotifyPetLevelUp(ClientNode* Client); //588
void RequestUpdatePetName(ClientNode* Client, BYTE* Body, size_t BodyLen); //178
void ResponseUpdatePetName(ClientNode* Client); //178
void NotifyPetUpdateName(ClientNode* Client); //590
void RequestGetCommodityExchangeItems(ClientNode* Client, BYTE* Body, size_t BodyLen); //171
void ResponseGetCommodityExchangeItems(ClientNode* Client); //171
void NotifyFileCheckList(ClientNode* Client); //862
void RequestFileCheck(ClientNode* Client, BYTE* Body, size_t BodyLen); //177
void NotifyKubiGameInfo(ClientNode* Client); //600
void RequestGainKubi(ClientNode* Client, BYTE* Body, size_t BodyLen); //180
void ResponseGainKubi(ClientNode* Client); //180
void NotifyGainKubi(ClientNode* Client); //601
void RequestDropKubi(ClientNode* Client, BYTE* Body, size_t BodyLen); //181
void ResponseDropKubi(ClientNode* Client); //181
void NotifyDropKubi(ClientNode* Client); //602
void NotifyKubiCountDown(ClientNode* Client); //603
void NotifyKubiQuarterOver(ClientNode* Client); //604
void NotifyKubiKickPlayer(ClientNode* Client); //605
void NotifyKubiPlayerLeave(ClientNode* Client); //606
void NotifyKubiRaceOver(ClientNode* Client); //607
void RequestReturnToHall(ClientNode* Client, BYTE* Body, size_t BodyLen); //182
void ResponseReturnToHall(ClientNode* Client); //182
void NotifyGuildBroadcast(ClientNode* Client); //15218
void NotifyGSvrdUpdatePlayerGuildScore(ClientNode* Client); //15219
void RequestCreateTeam(ClientNode* Client, BYTE* Body, size_t BodyLen); //191
void ResponseCreateTeam(ClientNode* Client); //191
void RequestJoinTeam(ClientNode* Client, BYTE* Body, size_t BodyLen); //192
void ResponseJoinTeam(ClientNode* Client); //192
void NotifyGuildMatchInfo(ClientNode* Client); //591
void NotifyGuildOneMemberMatchInfo(ClientNode* Client); //592
void NotifyJoinTeam(ClientNode* Client); //611
void RequestRemoveTeamMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //193
void ResponseRemoveTeamMember(ClientNode* Client); //193
void RequestQuitTeam(ClientNode* Client, BYTE* Body, size_t BodyLen); //194
void ResponseQuitTeam(ClientNode* Client); //194
void NotifyQuitTeam(ClientNode* Client); //612
void RequestGetTeamList(ClientNode* Client, BYTE* Body, size_t BodyLen); //195
void ResponseGetTeamList(ClientNode* Client); //195
void RequestGetTeamListByGuildName(ClientNode* Client, BYTE* Body, size_t BodyLen); //198
void ResponseGetTeamListByGuildName(ClientNode* Client); //198
void RequestGetTeamMemeberList(ClientNode* Client, BYTE* Body, size_t BodyLen); //196
void ResponseGetTeamMemeberList(ClientNode* Client); //196
void RequestTeamInvitePlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //197
void ResponseTeamInvitePlayer(ClientNode* Client); //197
void NotifyBeTeamInvited(ClientNode* Client); //613
void RequestCreateTeamRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //211
void ResponseCreateTeamRoom(ClientNode* Client); //211
void NotifyCreateTeamRoom(ClientNode* Client); //623
void RequestEnterTeamRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //212
void ResponseEnterTeamRoom(ClientNode* Client); //212
void NotifyRoomAndOtherTeamInfo(ClientNode* Client); //624
void NotifyTeamInfo(ClientNode* Client); //621
void RequestLeaveTeamRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //213
void ResponseLeaveTeamRoom(ClientNode* Client); //213
void NotifyLeaveTeamRoom(ClientNode* Client); //622
void RequestKickFromTeamRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //215
void ResponseKickFromTeamRoom(ClientNode* Client); //215
void NotifyKickFromTeamRoom(ClientNode* Client); //625
void RequestGetTeamRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //214
void ResponseGetTeamRoomList(ClientNode* Client); //214
void RequestGetTeamRoomListByGuildName(ClientNode* Client, BYTE* Body, size_t BodyLen); //219
void ResponseGetTeamRoomListByGuildName(ClientNode* Client); //219
void NotifyTeamRaceOver(ClientNode* Client); //626
void RequestInviteTeamIntoRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //216
void ResponseInviteTeamIntoRoom(ClientNode* Client); //216
void NotifyTeamBeInvitedIntoRoom(ClientNode* Client); //627
void NotifyOtherTeamSelfInfo(ClientNode* Client); //628
void NotifyTeamMatchNotice(ClientNode* Client); //629
void RequestQuickEnterTeamRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //220
void ResponseQuickEnterTeamRoom(ClientNode* Client); //220
void RequestGetLimitKartList(ClientNode* Client, BYTE* Body, size_t BodyLen); //217
void ResponseGetLimitKartList(ClientNode* Client); //217
void RequestScoreRules(ClientNode* Client, BYTE* Body, size_t BodyLen); //218
void ResponseGetScoreRules(ClientNode* Client); //218
void RequestGetMemberInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //200
void ResponseGetMemberInfo(ClientNode* Client); //200
void RequestGetAllTeam(ClientNode* Client, BYTE* Body, size_t BodyLen); //201
void ResponseGetAllTeam(ClientNode* Client); //201
void RequestChangeTeamLeader(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeTeamLeader(ClientNode* Client); //?
void NotifyChangeTeamLeader(ClientNode* Client); //?
void RequestEnterTeamMatchServer(ClientNode* Client, BYTE* Body, size_t BodyLen); //250
void ResponseEnterTeamMatchServer(ClientNode* Client); //250
void NotifyTopListDesc(ClientNode* Client); //701
void RequestTopList(ClientNode* Client, BYTE* Body, size_t BodyLen); //461
void ResponseTopList(ClientNode* Client); //461
void RequestDanceGetRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //251
void ResponseDanceGetRoomList(ClientNode* Client); //251
void RequestDanceEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //252
void ResponseDanceEnterRoom(ClientNode* Client); //252
void NotifyEnterDanceRoomMoreInfo(ClientNode* Client); //226
void RequestDanceChangeMusic(ClientNode* Client, BYTE* Body, size_t BodyLen); //253
void ResponseDanceChangeMusic(ClientNode* Client); //253
void NotifyDanceChangeMusic(ClientNode* Client); //721
void RequestChangeScene(ClientNode* Client, BYTE* Body, size_t BodyLen); //254
void ResponseChangeScene(ClientNode* Client); //254
void NotifyChangeScene(ClientNode* Client); //722
void NotifyDanceGameBegin(ClientNode* Client); //726
void NotifyDanceWaitUnReadyPlayers(ClientNode* Client); //727
void RequestDancePrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen); //259
void NotifyDanceRaceBegin(ClientNode* Client); //728
void NotifyDanceShow(ClientNode* Client); //729
void NotifyDanceRaceOver(ClientNode* Client); //730
void NotifyDanceGameOver(ClientNode* Client); //731
void RequestDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen); //260
void ResponseDanceStepStatistics(ClientNode* Client); //260
void NotifyDanceStepStatistics(ClientNode* Client); //?
void NotifyDanceRank(ClientNode* Client); //733
void RequestGetInviteList(ClientNode* Client, BYTE* Body, size_t BodyLen); //255
void ResponseGetInviteList(ClientNode* Client); //255
void RequestDanceQuickEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //256
void ResponseDanceQuickEnterRoom(ClientNode* Client); //256
void NotifyQuickEnterDanceRoomMoreInfo(ClientNode* Client); //227
void NotifySkillStoneKartInfo(ClientNode* Client); //228
void RequestDanceChangeMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //257
void ResponseDanceChangeMode(ClientNode* Client); //257
void NotifyDanceChangeMode(ClientNode* Client); //723
void RequestDanceChangeRandKeyFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //258
void ResponseDanceChangeRandKeyFlag(ClientNode* Client); //258
void NotifyDanceChangeRandKeyFlag(ClientNode* Client); //724
void RequestAffection(ClientNode* Client, BYTE* Body, size_t BodyLen); //305
void NotifyAffection(ClientNode* Client); //593
void RequestAKAffection(ClientNode* Client, BYTE* Body, size_t BodyLen); //306
void NotifyAKAffection(ClientNode* Client); //594
void RequestChangeRoomName(ClientNode* Client, BYTE* Body, size_t BodyLen); //222
void ResponseChangeRoomName(ClientNode* Client); //222
void NotifyChangeRoomName(ClientNode* Client); //598
void NotifyNPCInfo(ClientNode* Client); //863
void RequestGetPkableNPCInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //431
void ResponseGetPkableNPCInfo(ClientNode* Client); //431
void RequestCheckNickName(ClientNode* Client, BYTE* Body, size_t BodyLen); //432
void ResponseCheckNickName(ClientNode* Client); //432
void RequestSetPkableNPCInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //433
void ResponseSetPkableNPCInfo(ClientNode* Client); //433
void NotifySetPkableNPCInfo(ClientNode* Client); //434
void RequestNPCDoAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //435
void ResponseNPCDoAction(ClientNode* Client); //435
void NotifyNPCDoAction(ClientNode* Client); //436
void NotifyChairInfo(ClientNode* Client); //864
void RequestChangeChairState(ClientNode* Client, BYTE* Body, size_t BodyLen); //360
void RequestReportListenMusic(ClientNode* Client, BYTE* Body, size_t BodyLen); //361
void ResponseChangeChairState(ClientNode* Client); //360
void NotifyChangeChairState(ClientNode* Client); //865
void RequestChangeUdpState(ClientNode* Client, BYTE* Body, size_t BodyLen); //179
void RequestDeleteOneItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //261
void ResponseDeleteOneItem(ClientNode* Client); //261
void NotifyRunnerInitInfo(ClientNode* Client); //741
void NotifyRunnerReportPos(ClientNode* Client); //742
void NotifyRunnerBoltResult(ClientNode* Client); //743
void NotifyRunnerHPChange(ClientNode* Client); //744
void NotifyRunnerRoleChange(ClientNode* Client); //745
void RequestRunnerReportPos(ClientNode* Client, BYTE* Body, size_t BodyLen); //321
void RequestRunnerOverTake(ClientNode* Client, BYTE* Body, size_t BodyLen); //322
void ResponseRunnerOverTake(ClientNode* Client); //322
void RequestRunnerBuyNo2(ClientNode* Client, BYTE* Body, size_t BodyLen); //323
void ResponseRunnerBuyNo2(ClientNode* Client); //323
void RequestChangeTempEffect(ClientNode* Client, BYTE* Body, size_t BodyLen); //221
void ResponseChangeTempEffect(ClientNode* Client); //221
void NotifyChangeTempEffect(ClientNode* Client); //595
void NotifyShooterInitInfo(ClientNode* Client); //771
void NotifyShooterGunPhysParam(ClientNode* Client); //?
void NotifyShooterMissilePhysParam(ClientNode* Client); //?
void NotifyShooterDestroy(ClientNode* Client); //774
void NotifyShooterMissileDenDeter(ClientNode* Client); //775
void NotifyShooterMissileResult(ClientNode* Client); //776
void NotifyShooterCurrentHP(ClientNode* Client); //777
void RequestShooterDestroyed(ClientNode* Client, BYTE* Body, size_t BodyLen); //332
void RequestShooterRecover(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestShooterMissileAttDeter(ClientNode* Client, BYTE* Body, size_t BodyLen); //334
void ResponseShooterMissileAttDeter(ClientNode* Client); //334
void RequestShooterMissileAttRes(ClientNode* Client, BYTE* Body, size_t BodyLen); //335
void RequestShooterMissileDenRes(ClientNode* Client, BYTE* Body, size_t BodyLen); //336
void RequestShooterReportCurrentHP(ClientNode* Client, BYTE* Body, size_t BodyLen); //337
void RequestReportCurrentNPCInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //185
void NotifyNPCWeedOut(ClientNode* Client); //186
void NotifyMsgBox(ClientNode* Client); //596
void NotifyNianShouInfo(ClientNode* Client); //597
void NotifyRandRoomNameList(ClientNode* Client); //760
void RequestGetLuckAwardList(ClientNode* Client, BYTE* Body, size_t BodyLen); //172
void ResponseGetLuckAwardList(ClientNode* Client); //172
void RequestGetRandomTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //187
void ResponseGetRandomTask(ClientNode* Client); //187
void RequestGetSpecialBroadcasts(ClientNode* Client, BYTE* Body, size_t BodyLen); //362
void ResponseGetSpecialBroadcasts(ClientNode* Client); //362
void RequestFishRegister(ClientNode* Client, BYTE* Body, size_t BodyLen); //10500
void ResponseFishRegister(ClientNode* Client); //10500
void RequestFishLogin(ClientNode* Client, BYTE* Body, size_t BodyLen); //10501
void ResponseFishLogin(ClientNode* Client); //10501
void RequestFishEnter(ClientNode* Client, BYTE* Body, size_t BodyLen); //10503
void ResponseFishEnter(ClientNode* Client); //10503
void RequestFishExit(ClientNode* Client, BYTE* Body, size_t BodyLen); //10504
void ResponseFishExit(ClientNode* Client); //10504
void RequestFishGetFishInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10505
void ResponseFishGetFishInfo(ClientNode* Client); //10505
void RequestFishGetLeaveWord(ClientNode* Client, BYTE* Body, size_t BodyLen); //10506
void ResponseFishGetLeaveWord(ClientNode* Client); //10506
void RequestFishGetMsg(ClientNode* Client, BYTE* Body, size_t BodyLen); //10507
void ResponseFishGetMsg(ClientNode* Client); //10507
void RequestFishGetBulletin(ClientNode* Client, BYTE* Body, size_t BodyLen); //10508
void ResponseFishGetBulletin(ClientNode* Client); //10508
void RequestFishGetHarvestInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10509
void ResponseFishGetHarvestInfo(ClientNode* Client); //10509
void RequestFishGetStorageInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10510
void ResponseFishGetStorageInfo(ClientNode* Client); //10510
void RequestFishStartFeedFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10514
void ResponseFishStartFeedFish(ClientNode* Client); //10514
void RequestFishHarvestFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10511
void ResponseFishHarvestFish(ClientNode* Client); //10511
void RequestFishHarvestAllFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10517
void ResponseFishHarvestAllFish(ClientNode* Client); //10517
void RequestFishUseFeed(ClientNode* Client, BYTE* Body, size_t BodyLen); //10512
void ResponseFishUseFeed(ClientNode* Client); //10512
void RequestFishSellFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10515
void ResponseFishSellFish(ClientNode* Client); //10515
void RequestFishSellAllFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10516
void ResponseFishSellAllFish(ClientNode* Client); //10516
void RequestFishBuyFishStock(ClientNode* Client, BYTE* Body, size_t BodyLen); //10518
void ResponseFishBuyFishStock(ClientNode* Client); //10518
void RequestFishGetGiftBoxInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10519
void ResponseFishGetGiftBoxInfo(ClientNode* Client); //10519
void RequestFishThrowRubbish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10521
void ResponseFishThrowRubbish(ClientNode* Client); //10521
void RequestFishClearRubbish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10522
void ResponseFishClearRubbish(ClientNode* Client); //10522
void RequestFishStealFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //10523
void ResponseFishStealFish(ClientNode* Client); //10523
void RequestFishLeaveWord(ClientNode* Client, BYTE* Body, size_t BodyLen); //10524
void ResponseFishLeaveWord(ClientNode* Client); //10524
void RequestFishReceiveGift(ClientNode* Client, BYTE* Body, size_t BodyLen); //10525
void ResponseFishReceiveGift(ClientNode* Client); //10525
void RequestFishGetPlayerAllFishInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10526
void ResponseFishGetPlayerAllFishInfo(ClientNode* Client); //10526
void NotifyClientReceiveNewLeaveWord(ClientNode* Client); //10550
void NotifyClientReceiveNewMsg(ClientNode* Client); //10551
void NotifyClientFishStealed(ClientNode* Client); //10552
void NotifyClientRubbishThrown(ClientNode* Client); //10553
void NotifyClientUpdateFishInfo(ClientNode* Client); //10554
void NotifyClientTimeOutAtOtherStock(ClientNode* Client); //10555
void NotifyClientRubbishCleared(ClientNode* Client); //10557
void NotifyClientHaveNewGift(ClientNode* Client); //10559
void NotifyClientCloseFishsys(ClientNode* Client); //10560
void RequestFishGetPlayerList(ClientNode* Client, BYTE* Body, size_t BodyLen); //10532
void ResponseFishGetPlayerList(ClientNode* Client); //10532
void RequestFishQueryPlayerInfoInList(ClientNode* Client, BYTE* Body, size_t BodyLen); //10533
void ResponseFishQueryPlayerInfoInList(ClientNode* Client); //10533
void RequestGetMaster(ClientNode* Client, BYTE* Body, size_t BodyLen); //363
void ResponseGetMaster(ClientNode* Client); //363
void RequestGetPrentices(ClientNode* Client, BYTE* Body, size_t BodyLen); //364
void ResponseGetPrentices(ClientNode* Client); //364
void RequestGetClassMates(ClientNode* Client, BYTE* Body, size_t BodyLen); //365
void ResponseGetClassMates(ClientNode* Client); //365
void RequestQueryMPAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //366
void ResponseQueryMPAward(ClientNode* Client); //366
void RequestAcc(ClientNode* Client, BYTE* Body, size_t BodyLen); //367
void ResponseAcc(ClientNode* Client); //367
void RequestDismiss(ClientNode* Client, BYTE* Body, size_t BodyLen); //368
void ResponseDismiss(ClientNode* Client); //368
void RequestGetMPAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //369
void ResponseGetMPAward(ClientNode* Client); //369
void NotifyMPAward(ClientNode* Client); //758
void RequestGetCommendMP(ClientNode* Client, BYTE* Body, size_t BodyLen); //370
void ResponseGetCommendMP(ClientNode* Client); //370
void NotifyReqAcc(ClientNode* Client); //751
void AckReqAcc(ClientNode* Client, BYTE* Body, size_t BodyLen); //751
void NotifyAccResult(ClientNode* Client); //752
void NotifyGraduate(ClientNode* Client); //753
void NotifyDismiss(ClientNode* Client); //754
void NotifyIncMasterPoint(ClientNode* Client); //755
void NotifyIncMaxPrenticeNum(ClientNode* Client); //756
void NotifyPMAward(ClientNode* Client); //757
void RequestGetPlayerSummaryInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //371
void ResponseGetPlayerSummaryInfo(ClientNode* Client); //371
void RequestGetMPAwardRule(ClientNode* Client, BYTE* Body, size_t BodyLen); //372
void ResponseGetMPAwardRule(ClientNode* Client); //372
void RequestReceiveTaskAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //188
void ResponseReceiveTaskAward(ClientNode* Client); //188
void NotifyRRModeExtraInfo(ClientNode* Client); //782
void NotifyBatonPassOn(ClientNode* Client); //780
void RequestBatonPassOn(ClientNode* Client, BYTE* Body, size_t BodyLen); //230
void ResponseBatonPassOn(ClientNode* Client); //230
void NotifyBatonExplosion(ClientNode* Client); //781
void NotifyRelayRaceOver(ClientNode* Client); //783
void RequestGetAchieveList(ClientNode* Client, BYTE* Body, size_t BodyLen); //373
void ResponseGetAchieveList(ClientNode* Client); //373
void RequestQueryAchieveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //374
void ResponseQueryAchieveAward(ClientNode* Client); //374
void RequestGetAchieveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //375
void ResponseGetAchieveAward(ClientNode* Client); //375
void NotifyUpdateAchieveProgress(ClientNode* Client); //759
void RequestStartShadowChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //1500
void ResponseStartShadowChallenge(ClientNode* Client); //1500
void RequestEndShadowChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //1501
void ResponseEndShadowChallenge(ClientNode* Client); //1501
void NotifyPropPoint(ClientNode* Client); //1502
void RequestCheckRealName(ClientNode* Client, BYTE* Body, size_t BodyLen); //1499
void ResponseCheckRealName(ClientNode* Client); //1499
void NotifyPlayerIdentify(ClientNode* Client); //608
void RequestRecommendGuildList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15020
void ResponseRecommendGuildList(ClientNode* Client); //15020
void RequestGetGuildChatRoomInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //380
void ResponseGetGuildChatRoomInfo(ClientNode* Client); //380
void RequestEnterGuildRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11011
void ResponseEnterGuildRoom(ClientNode* Client); //11011
void NotifyGuildRoomMoreInfo(ClientNode* Client); //11019
void RequestLeaveGuildRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11012
void ResponseLeaveGuildRoom(ClientNode* Client); //11012
void RequestKickOtherFromGuildRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11013
void ResponseKickOtherFromGuildRoom(ClientNode* Client); //11013
void NotifyKickFromGuildRoom(ClientNode* Client); //11014
void NotifyOtherEnterGuildRoom(ClientNode* Client); //11015
void NotifyOtherLeavedGuildRoom(ClientNode* Client); //11016
void NotifySwitchGuildChatServer(ClientNode* Client); //11017
void RequestChangeOBState(ClientNode* Client, BYTE* Body, size_t BodyLen); //134
void ResponseChangeOBState(ClientNode* Client); //134
void NotifyChangeOBState(ClientNode* Client); //609
void RequestParticipateLuckyMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //400
void ResponseParticipateLuckyMatch(ClientNode* Client); //400
void RequestCancelParticipateLuckyMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //401
void ResponseCancelParticipateLuckyMatch(ClientNode* Client); //401
void NotifyParticipateLuckyMatchTimeOut(ClientNode* Client); //816
void RequestLuckyMatchBillboard(ClientNode* Client, BYTE* Body, size_t BodyLen); //402
void ResponseLuckyMatchBillboard(ClientNode* Client); //402
void NotifySvrConfig(ClientNode* Client); //800
void RequestLmtEnterChatRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //381
void ResponseLmtEnterChatRoom(ClientNode* Client); //381
void RequestLmtUpdateStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //382
void ResponseLmtUpdateStatus(ClientNode* Client); //382
void RequestLmtGetScoreInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //383
void ResponseLmtGetScoreInfo(ClientNode* Client); //383
void RequestLmtGetElimInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //384
void ResponseLmtGetElimInfo(ClientNode* Client); //384
void RequestLmtRoll(ClientNode* Client, BYTE* Body, size_t BodyLen); //385
void ResponseLmtRoll(ClientNode* Client); //385
void NotifyLuckyMatchReady(ClientNode* Client); //815
void NotifyLmtEnterRoom(ClientNode* Client); //801
void NotifyLmtLeaveRoom(ClientNode* Client); //802
void NotifyLmtUpdateStatus(ClientNode* Client); //803
void NotifyLmtOpponentInfo(ClientNode* Client); //804
void NotifyLmtMatchOver(ClientNode* Client); //805
void NotifyLmtRoll(ClientNode* Client); //806
void NotifyLmtAllRollAward(ClientNode* Client); //807
void NotifyLmtBroadCast(ClientNode* Client); //808
void NotifyLmtGetElimInfo(ClientNode* Client); //809
void NotifyLmtGetScoreInfo(ClientNode* Client); //810
void NotifyLmtSummaryInfo(ClientNode* Client); //811
void NotifyAddOverdueItem(ClientNode* Client); //931
void NotifyDelOverdueItem(ClientNode* Client); //932
void RequestDelOverdueItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //933
void ResponseDelOverdueItem(ClientNode* Client); //933
void RequestInlaySkillStone(ClientNode* Client, BYTE* Body, size_t BodyLen); //901
void ResponseInlaySkillStone(ClientNode* Client); //901
void RequestAddStoneGroove(ClientNode* Client, BYTE* Body, size_t BodyLen); //903
void ResponseAddStoneGroove(ClientNode* Client); //903
void RequestCompositeSkillStone(ClientNode* Client, BYTE* Body, size_t BodyLen); //905
void ResponseCompositeSkillStone(ClientNode* Client); //905
void NotifyUpdateKartSkillStoneInfo(ClientNode* Client); //906
void NotifyOtherKartStoneInfo(ClientNode* Client); //907
void NotifyAddPropBySkillStone(ClientNode* Client); //908
void RequestReportSkillStoneTakeEffect(ClientNode* Client, BYTE* Body, size_t BodyLen); //909
void NotifyOtherSkillStoneTakeEffect(ClientNode* Client); //910
void RequestReportSkillStoneTakeEffectForStatistic(ClientNode* Client, BYTE* Body, size_t BodyLen); //911
void RequestRemoveSkillStone(ClientNode* Client, BYTE* Body, size_t BodyLen); //912
void ResponseRemoveSkillStone(ClientNode* Client); //912
void RequestAskGuildBonus(ClientNode* Client, BYTE* Body, size_t BodyLen); //941
void ResponseAskGuildBonus(ClientNode* Client); //941
void NotifyLeaderAskGuildBonus(ClientNode* Client); //942
void RequestReplyAskGuildBonus(ClientNode* Client, BYTE* Body, size_t BodyLen); //943
void RequestReportCheckData(ClientNode* Client, BYTE* Body, size_t BodyLen); //377
void RequestSampleCheckPointData(ClientNode* Client, BYTE* Body, size_t BodyLen); //270
void RequestFizzInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //944
void ResponseFizzInfo(ClientNode* Client); //944
void RequestFizzLottery(ClientNode* Client, BYTE* Body, size_t BodyLen); //945
void ResponseFizzLottery(ClientNode* Client); //945
void NotifyFizzInfo(ClientNode* Client); //946
void NotifyDeleteFizzTask(ClientNode* Client); //947
void AckMultiSynchronize(ClientNode* Client, BYTE* Body, size_t BodyLen); //1503
void NotifyMultiSynchronize(ClientNode* Client); //1503
void RequestGetExchangeDesc(ClientNode* Client, BYTE* Body, size_t BodyLen); //936
void ResponseGetExchangeDesc(ClientNode* Client); //936
void RequestReportFeedBack(ClientNode* Client, BYTE* Body, size_t BodyLen); //934
void NotifyFeedBackData(ClientNode* Client); //935
void RequestGetMailHeaderList(ClientNode* Client, BYTE* Body, size_t BodyLen); //406
void ResponseGetMailHeaderList(ClientNode* Client); //406
void RequestGetMailBody(ClientNode* Client, BYTE* Body, size_t BodyLen); //407
void ResponseGetMailBody(ClientNode* Client); //407
void RequestGetMailAttach(ClientNode* Client, BYTE* Body, size_t BodyLen); //408
void ResponseGetMailAttach(ClientNode* Client); //408
void RequestSendMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //409
void ResponseSendMail(ClientNode* Client); //409
void RequestModifyMailFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //410
void ResponseModifyMailFlag(ClientNode* Client); //410
void RequestDeleteMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //411
void ResponseDeleteMail(ClientNode* Client); //411
void NotifyNewMailHeader(ClientNode* Client); //412
void NotifyMailSomeFlag(ClientNode* Client); //413
void RequestChangeMailSomeFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //414
void ResponseChangeMailSomeFlag(ClientNode* Client); //414
void RequestGetAnonymMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //426
void ResponseGetAnonymMail(ClientNode* Client); //426
void RequestReplyAnonymMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //427
void ResponseReplyAnonymMail(ClientNode* Client); //427
void RequestRecycleAnonymMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //428
void ResponseRecycleAnonymMail(ClientNode* Client); //428
void RequestGuildWelfareInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //15022
void ResponseGuildWelfareInfo(ClientNode* Client); //15022
void RequestGuildListOtherInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildListOtherInfo(ClientNode* Client); //15021
void RequestDayProsperityAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //15023
void ResponseDayProsperityAward(ClientNode* Client); //15023
void NotifyLastProsperityAward(ClientNode* Client); //15224
void RequestEltQQOnlineFriends(ClientNode* Client, BYTE* Body, size_t BodyLen); //10900
void ResponseEltQQOnlineFriends(ClientNode* Client); //10900
void NotifyClientEnlistGuid(ClientNode* Client); //10913
void RequestEltEnlist(ClientNode* Client, BYTE* Body, size_t BodyLen); //10901
void ResponseEltEnlist(ClientNode* Client); //10901
void RequestEltEnlistAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //10902
void ResponseEltEnlistAward(ClientNode* Client); //10902
void RequestGetConItemLeftNum(ClientNode* Client, BYTE* Body, size_t BodyLen); //10903
void ResponseGetConItemLeftNum(ClientNode* Client); //10903
void RequestReportCheat(ClientNode* Client, BYTE* Body, size_t BodyLen); //1600
void ResponseReportCheat(ClientNode* Client); //1600
void NotifyCheatWarning(ClientNode* Client); //1601
void RequestGetWareHouseStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //420
void ResponseGetWareHouseStatus(ClientNode* Client); //420
void RequestGetWareHouseItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //421
void ResponseGetWareHouseItemList(ClientNode* Client); //421
void RequestDoWareHouseOperation(ClientNode* Client, BYTE* Body, size_t BodyLen); //422
void ResponseWareHouseOperation(ClientNode* Client); //422
void NotifyWareHouseDelItem(ClientNode* Client); //423
void RequestReportN2OChangeEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //450
void RequestUseHyperJet(ClientNode* Client, BYTE* Body, size_t BodyLen); //451
void RequestLoverDanceChangeOneMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //262
void ResponseLoverDanceChangeOneMode(ClientNode* Client); //262
void NotifyLoverDanceChangeOneMode(ClientNode* Client); //725
void RequestLoverDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen); //263
void NotifyLoverDanceStepStatistics(ClientNode* Client); //735
void NotifyLoverDanceWaitCooperKey(ClientNode* Client); //736
void RequestLoverDanceCooperKey(ClientNode* Client, BYTE* Body, size_t BodyLen); //264
void NotifyLoverDanceCooperKey(ClientNode* Client); //737
void RequestGetFavoriteTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //415
void ResponseGetFavoriteTask(ClientNode* Client); //415
void RequestAddFavoriteTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //416
void ResponseAddFavoriteTask(ClientNode* Client); //416
void RequestDeleteFavoriteTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //417
void ResponseDeleteFavoriteTask(ClientNode* Client); //417
void NotifyDeleteOneItem(ClientNode* Client); //610
void RequestLoveDanceShowTimeAffection(ClientNode* Client, BYTE* Body, size_t BodyLen); //265
void ResponseLoveDanceShowTimeAffection(ClientNode* Client); //265
void NotifyLoveDanceShowTimeAffection(ClientNode* Client); //738
void RequestGetPetSkillList(ClientNode* Client, BYTE* Body, size_t BodyLen); //440
void ResponseGetPetSkillList(ClientNode* Client); //440
void RequestSetSecPwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //441
void ResponseSetSecPwd(ClientNode* Client); //441
void RequestModSecPwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //442
void ResponseModSecPwd(ClientNode* Client); //442
void RequestEmptySecPwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //443
void ResponseEmptySecPwd(ClientNode* Client); //443
void RequestCancelEmptySecPwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //444
void ResponseCancelEmptySecPwd(ClientNode* Client); //444
void RequestCheckSecPwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //445
void ResponseCheckSecPwd(ClientNode* Client); //445
void RequestGetSecPwdStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //447
void ResponseGetSecPwdStatus(ClientNode* Client); //447
void NotifyS2CEvent(ClientNode* Client); //446
void RequestGetShoppingCarItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //452
void ResponseGetShoppingCarItemList(ClientNode* Client); //452
void RequestUpdateShoppingCarItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //453
void ResponseUpdateShoppingCarItemList(ClientNode* Client); //453
void RequestTakeStealPigTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //11024
void ResponseTakeStealPigTask(ClientNode* Client); //11024
void RequestTransferToGuildRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11025
void ResponseTransferToGuildRoom(ClientNode* Client); //11025
void RequestGuildRoomPigInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11026
void ResponseGuildRoomPigInfo(ClientNode* Client); //11026
void NotifyGuildRoomPigInfo(ClientNode* Client); //11027
void RequestDigPig(ClientNode* Client, BYTE* Body, size_t BodyLen); //11028
void ResponseDigPig(ClientNode* Client); //11028
void NotifyDigPig(ClientNode* Client); //11029
void RequestGetPig(ClientNode* Client, BYTE* Body, size_t BodyLen); //11030
void ResponseGetPig(ClientNode* Client); //11030
void NotifyGetPig(ClientNode* Client); //11031
void RequestSubmitPig(ClientNode* Client, BYTE* Body, size_t BodyLen); //11032
void ResponseSubmitPig(ClientNode* Client); //11032
void NotifySubmitPig(ClientNode* Client); //11033
void NotifyStealPigStatus(ClientNode* Client); //11034
void RequestModifyGuildEnlistCondition(ClientNode* Client, BYTE* Body, size_t BodyLen); //15026
void ResponseModifyGuildEnlistCondition(ClientNode* Client); //15026
void RequestAdvanceQueryGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15025
void ResponseAdvanceQueryGuild(ClientNode* Client); //15025
void RequestModifyDutyProperty(ClientNode* Client, BYTE* Body, size_t BodyLen); //15032
void ResponseModifyDutyProperty(ClientNode* Client); //15032
void RequestApplyDuty(ClientNode* Client, BYTE* Body, size_t BodyLen); //15033
void ResponseApplyDuty(ClientNode* Client); //15033
void RequestDutyApplyList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15034
void ResponseDutyApplyList(ClientNode* Client); //15034
void RequestDutyApplyReply(ClientNode* Client, BYTE* Body, size_t BodyLen); //15035
void ResponseDutyApplyReply(ClientNode* Client); //15035
void RequestGetGuildCommercialInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //15028
void ResponseGetGuildCommercialInfo(ClientNode* Client); //15028
void RequestChangeGuildCloth(ClientNode* Client, BYTE* Body, size_t BodyLen); //15029
void ResponseChangeGuildCloth(ClientNode* Client); //15029
void NotifyModifyDutyRight(ClientNode* Client); //15223
void NotifyChangeGuildCloth(ClientNode* Client); //15227
void RequestTransferMapInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //462
void NotifyOtherClientMapInfo(ClientNode* Client); //463
void RequestTransferMusicResHoldInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //269
void NotifyTransferMusicResHoldInfo(ClientNode* Client); //266
void RequestTransferResourceDownloadStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //267
void NotifyResourceDownloadStatus(ClientNode* Client); //268
void NotifyClientVipFlag(ClientNode* Client); //948
void NotifyClientDeadLineItemTips(ClientNode* Client); //949
void NotifyClientDeadLineItemExpired(ClientNode* Client); //950
void RequestReportClickStream(ClientNode* Client, BYTE* Body, size_t BodyLen); //241
void NotifySvrConfig2(ClientNode* Client); //822
void RequestC2GGetHRoomNum(ClientNode* Client, BYTE* Body, size_t BodyLen); //11040
void ResponseC2GGetHRoomNum(ClientNode* Client); //11040
void RequestC2GGetHRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //11041
void ResponseC2GGetHRoomList(ClientNode* Client); //11041
void RequestC2GGetHRoomBookingInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11042
void ResponseC2GGetHRoomBookingInfo(ClientNode* Client); //11042
void RequestC2GGetHRoomPhyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11043
void ResponseC2GGetHRoomPhyInfo(ClientNode* Client); //11043
void RequestC2GBookingHRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11044
void ResponseC2GBookingHRoom(ClientNode* Client); //11044
void RequestC2GGetBookingRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11046
void ResponseC2GGetBookingRoom(ClientNode* Client); //11046
void RequestC2GSendWeddingMail(ClientNode* Client, BYTE* Body, size_t BodyLen); //11045
void ResponseC2GSendWeddingMail(ClientNode* Client); //11045
void NotifyG2CWeddingMsg(ClientNode* Client); //11047
void RequestG2CTodayPreWeddingStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //11048
void ResponseG2CTodayPreWeddingStatus(ClientNode* Client); //11048
void RequestC2HCEnterHRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //11060
void ResponseC2HCEnterHRoom(ClientNode* Client); //11060
void RequestC2HCGetHRoomInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11061
void ResponseC2HCGetHRoomInfo(ClientNode* Client); //11061
void RequestC2HCModifyHRoomInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11062
void ResponseC2HCModifyHRoomInfo(ClientNode* Client); //11062
void RequestC2HCGetHRoomStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //11063
void ResponseC2HCGetHRoomStatus(ClientNode* Client); //11063
void RequestC2HCSwitchHRoomStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //11064
void ResponseC2HCSwitchHRoomStatus(ClientNode* Client); //11064
void RequestC2HCInviteWeddingGuest(ClientNode* Client, BYTE* Body, size_t BodyLen); //11065
void ResponseC2HCInviteWeddingGuest(ClientNode* Client); //11065
void RequestC2HCReportQTEAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //11066
void ResponseC2HCReportQTEAction(ClientNode* Client); //11066
void RequestC2HCPickupItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //11067
void ResponseC2HCPickupItem(ClientNode* Client); //11067
void RequestC2HCKickPlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //11068
void ResponseC2HCKickPlayer(ClientNode* Client); //11068
void RequestC2CKickPlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //1670
void ResponseC2CKickplayer(ClientNode* Client); //1670
void NotifyC2CLeaveRoom(ClientNode* Client); //1671
void RequestC2HCGetAllGenItems(ClientNode* Client, BYTE* Body, size_t BodyLen); //11069
void ResponseC2HCGetAllGenItems(ClientNode* Client); //11069
void NotifyHC2CWeddingStatus(ClientNode* Client); //11070
void NotifyHC2CQTEEvent(ClientNode* Client); //11071
void NotifyHC2CQTEResult(ClientNode* Client); //11076
void NotifyHC2CGenItemEvent(ClientNode* Client); //11072
void NotifyHC2CPickUpItem(ClientNode* Client); //11073
void NotifyHC2CWeddingBroadcast(ClientNode* Client); //11074
void NotifyHC2CLeaveHRoom(ClientNode* Client); //11075
void RequestGetGuildMemberList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15037
void ResponseGetGuildMemberList(ClientNode* Client); //15037
void RequestC2GCancelHRoomBooking(ClientNode* Client, BYTE* Body, size_t BodyLen); //11049
void ResponseC2GCancelHRoomBooking(ClientNode* Client); //11049
void RequestKartRefitInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //271
void ResponseKartRefitInfo(ClientNode* Client); //271
void RequestShapeRefit(ClientNode* Client, BYTE* Body, size_t BodyLen); //272
void ResponseShapeRefit(ClientNode* Client); //272
void RequestCancelShapeRefit(ClientNode* Client, BYTE* Body, size_t BodyLen); //273
void ResponseCancelShapeRefit(ClientNode* Client); //273
void RequestCheckGuanJiaStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //651
void ResponseCheckGuanJiaStatus(ClientNode* Client); //651
void RequestSNSRegister(ClientNode* Client, BYTE* Body, size_t BodyLen); //10850
void ResponseSNSRegister(ClientNode* Client); //10850
void RequestQuitSNS(ClientNode* Client, BYTE* Body, size_t BodyLen); //10851
void ResponseQuitSNS(ClientNode* Client); //10851
void RequestUpdateSNSInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10852
void ResponseUpdateSNSInfo(ClientNode* Client); //10852
void RequestGetPlayerSNSInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //10853
void ResponseGetPlayerSNSInfo(ClientNode* Client); //10853
void RequestInviteEnterSNSGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //10854
void ResponseInviteEnterSNSGame(ClientNode* Client); //10854
void NotifyInvitedSNSGame(ClientNode* Client); //10855
void AckInvitedSNSGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //10855
void NotifyEnterSNSGame(ClientNode* Client); //10856
void RequestEnterSNSGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //10857
void ResponseEnterSNSGame(ClientNode* Client); //10857
void RequestAllocSNSServer(ClientNode* Client, BYTE* Body, size_t BodyLen); //10858
void ResponseAllocSNSServer(ClientNode* Client); //10858
void RequestMatchSNSGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //10859
void ResponseMatchSNSGame(ClientNode* Client); //10859
void NotifyMatchSNSGameResult(ClientNode* Client); //10860
void RequestGetSNSBroadcast(ClientNode* Client, BYTE* Body, size_t BodyLen); //10861
void ResponseGetSNSBroadcast(ClientNode* Client); //10861
void RequestSNSRecommand(ClientNode* Client, BYTE* Body, size_t BodyLen); //10862
void ResponseSNSRecommand(ClientNode* Client); //10862
void RequestCancelMatchSNSGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //10863
void ResponseCancelMatchSNSGame(ClientNode* Client); //10863
void RequestSNSLoverMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //10864
void ResponseSNSLoverMatch(ClientNode* Client); //10864
void RequestCancelSNSLoverMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //10865
void ResponseCancelSNSLoverMatch(ClientNode* Client); //10865
void NotifySNSLoverMatchResult(ClientNode* Client); //10866
void NotifySnsGameInviteFailed(ClientNode* Client); //10867
void RequestReportSNSPlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //10868
void ResponseReportSNSPlayer(ClientNode* Client); //10868
void RequestUpdateSNSFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //10869
void ResponseUpdateSNSFlag(ClientNode* Client); //10869
void RequestGetPlayerSignature(ClientNode* Client, BYTE* Body, size_t BodyLen); //378
void ResponseGetPlayerSignature(ClientNode* Client); //378
void RequestChangeRecommandStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //275
void ResponseChangeRecommandStatus(ClientNode* Client); //275
void NotifyRecommandResult(ClientNode* Client); //276
void RequestReportSnsPanelOpenCount(ClientNode* Client, BYTE* Body, size_t BodyLen); //10870
void RequestC2GGetChallengeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11210
void ResponseC2GGetChallengeInfo(ClientNode* Client); //11210
void RequestC2GGetGuildChallengeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11211
void ResponseC2GGetGuildChallengeInfo(ClientNode* Client); //11211
void RequestC2GGetMapsChallengeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //11212
void ResponseC2GGetMapsChallengeInfo(ClientNode* Client); //11212
void RequestC2GGetMapChallengeRank(ClientNode* Client, BYTE* Body, size_t BodyLen); //11213
void ResponseC2GGetMapChallengeRank(ClientNode* Client); //11213
void RequestC2GGetRecentChallengeMsg(ClientNode* Client, BYTE* Body, size_t BodyLen); //11214
void ResponseC2GGetRecentChallengeMsg(ClientNode* Client); //11214
void NotifyG2CGuildChallengeMsg(ClientNode* Client); //11215
void RequestC2GGetMapOwner(ClientNode* Client, BYTE* Body, size_t BodyLen); //11216
void ResponseC2GGetMapOwner(ClientNode* Client); //11216
void RequestC2GChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //11217
void ResponseC2GChallenge(ClientNode* Client); //11217
void RequestC2GCancelChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //11218
void ResponseC2GCancelChallenge(ClientNode* Client); //11218
void NotifyG2CLoadChallengeFile(ClientNode* Client); //11219
void NotifyC2GLoadChallengeFileResult(ClientNode* Client); //11220
void NotifyG2CStartChallenge(ClientNode* Client); //11221
void NotifyC2GStartChallengeResult(ClientNode* Client); //11222
void NotifyC2GChallengeBegin(ClientNode* Client); //11223
void NotifyG2CChallengeResult(ClientNode* Client); //11224
void RequestC2GUpdateChallengeRank(ClientNode* Client, BYTE* Body, size_t BodyLen); //11225
void ResponseC2GUpdateChallengeRank(ClientNode* Client); //11225
void RequestC2GCancelUpdateChallengeRank(ClientNode* Client, BYTE* Body, size_t BodyLen); //11226
void ResponseC2GCancelUpdateChallengeRank(ClientNode* Client); //11226
void NotifyG2CUpLoadChallengeFile(ClientNode* Client); //11227
void NotifyG2CUpdateChallengeRankResult(ClientNode* Client); //11228
void RequestC2GLoadFile(ClientNode* Client, BYTE* Body, size_t BodyLen); //11229
void ResponseC2GLoadFile(ClientNode* Client); //11229
void RequestC2GChallengeMapRecommend(ClientNode* Client, BYTE* Body, size_t BodyLen); //11230
void ResponseC2GChallengeMapRecommend(ClientNode* Client); //11230
void RequestC2GChallengeRankRecommend(ClientNode* Client, BYTE* Body, size_t BodyLen); //11231
void ResponseC2GChallengeRankRecommend(ClientNode* Client); //11231
void NotifyG2CChallengeRankRecommendDetail(ClientNode* Client); //11232
void RequestC2GChallengeCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //11233
void ResponseC2GChallengeCfg(ClientNode* Client); //11233
void RequestC2GChallengeReport(ClientNode* Client, BYTE* Body, size_t BodyLen); //11234
void ResponseC2GChallengeReport(ClientNode* Client); //11234
void NotifyAppellationList(ClientNode* Client); //1616
void RequestWearAppellation(ClientNode* Client, BYTE* Body, size_t BodyLen); //1618
void ResponseWearAppellation(ClientNode* Client); //1618
void RequestUnwearAppellation(ClientNode* Client, BYTE* Body, size_t BodyLen); //1619
void ResponseUnwearAppellation(ClientNode* Client); //1619
void NotifyUpdateAppellation(ClientNode* Client); //1620
void NotifyCurrentAppellationInRoom(ClientNode* Client); //1621
void RequestKartMaintenance(ClientNode* Client, BYTE* Body, size_t BodyLen); //10910
void ResponseKartMaintenance(ClientNode* Client); //10910
void RequestConsoleCmd(ClientNode* Client, BYTE* Body, size_t BodyLen); //652
void ResponseConsoleCmd(ClientNode* Client); //652
void RequestReportNewPlayerTutorStatistic(ClientNode* Client, BYTE* Body, size_t BodyLen); //951
void RequestGetPhantomN2O(ClientNode* Client, BYTE* Body, size_t BodyLen); //10915
void NotifyGetPhantomN2O(ClientNode* Client); //10916
void RequestStartPhantomN2OJet(ClientNode* Client, BYTE* Body, size_t BodyLen); //10917
void RequestEndPhantomN2OJet(ClientNode* Client, BYTE* Body, size_t BodyLen); //10918
void NotifyClientUpdateNobleInfo(ClientNode* Client); //961
void NotifyCustomMapList(ClientNode* Client); //631
void RequestUpdateCustomMapList(ClientNode* Client, BYTE* Body, size_t BodyLen); //1651
void ResponseUpdateCustomMapList(ClientNode* Client); //1651
void RequestChangeFishingStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //11400
void ResponseChangeFishingStatus(ClientNode* Client); //11400
void NotifyChangeFishingStatus(ClientNode* Client); //11401
void NotifyFishingResult(ClientNode* Client); //11402
void NotifyDragonBallQTEBegin(ClientNode* Client); //11403
void RequestReportDragonBallQTEResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //11404
void RequestRoastFish(ClientNode* Client, BYTE* Body, size_t BodyLen); //11405
void ResponseRoastFish(ClientNode* Client); //11405
void NotifyFBInitInfo(ClientNode* Client); //11362
void RequestFBReportTrigger(ClientNode* Client, BYTE* Body, size_t BodyLen); //11363
void RequestFBReportPlayerEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //11364
void RequestFBReportBossEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //11365
void NotifyFBPlayerEvent(ClientNode* Client); //11366
void NotifyFBBossEvent(ClientNode* Client); //11367
void NotifyFBAction(ClientNode* Client); //11368
void NotifyFBStatus(ClientNode* Client); //11369
void NotifyFBRaceOver(ClientNode* Client); //11370
void NotifyFBGenPropBox(ClientNode* Client); //11371
void RequestGetPlayerEventCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //11451
void ResponseGetPlayerEventCfg(ClientNode* Client); //11451
void RequestGetPlayerEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //11452
void ResponseGetPlayerEvent(ClientNode* Client); //11452
void RequestReadPlayerEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //11453
void ResponseReadPlayerEvent(ClientNode* Client); //11453
void RequestChangeFocus(ClientNode* Client, BYTE* Body, size_t BodyLen); //11454
void ResponseChangeFocus(ClientNode* Client); //11454
void RequestStartChallengeFriend(ClientNode* Client, BYTE* Body, size_t BodyLen); //11455
void ResponseStartChallengeFriend(ClientNode* Client); //11455
void RequestEndChallengeFriend(ClientNode* Client, BYTE* Body, size_t BodyLen); //11456
void ResponseEndChallengeFriend(ClientNode* Client); //11456
void NotifySpeed2Cfg(ClientNode* Client); //11358
void RequestChangeModel(ClientNode* Client, BYTE* Body, size_t BodyLen); //277
void ResponseChangeModel(ClientNode* Client); //277
void NotifyChangeModel(ClientNode* Client); //278
void RequestEnlistGuildMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //300
void ResponseEnlistGuildMember(ClientNode* Client); //300
void RequestModifyGuildName(ClientNode* Client, BYTE* Body, size_t BodyLen); //288
void ResponseModifyGuildName(ClientNode* Client); //288
void NotifyGUMCModifyGuildName(ClientNode* Client); //15235
void RequestGetSpringInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //280
void ResponseGetSpringInfo(ClientNode* Client); //280
void RequestEnterSpring(ClientNode* Client, BYTE* Body, size_t BodyLen); //281
void ResponseEnterSpring(ClientNode* Client); //281
void RequestLeaveSpring(ClientNode* Client, BYTE* Body, size_t BodyLen); //282
void ResponseLeaveSpring(ClientNode* Client); //282
void NotifyLeaveSpring(ClientNode* Client); //287
void NotifySpringHoleInfo(ClientNode* Client); //283
void NotifyBatheAward(ClientNode* Client); //284
void NotifyOutDoorEggDisappear(ClientNode* Client); //285
void NotifyEnterSpring(ClientNode* Client); //286
void RequestCrashModeIncEgg(ClientNode* Client, BYTE* Body, size_t BodyLen); //10920
void RequestCrashModeDecEgg(ClientNode* Client, BYTE* Body, size_t BodyLen); //10921
void RequestChangeCrashModeSponsor(ClientNode* Client, BYTE* Body, size_t BodyLen); //10922
void ResponseChangeCrashModeSponsor(ClientNode* Client); //10922
void RequestWorldOnlineInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //1400
void ResponseWorldOnlineInfo(ClientNode* Client); //1400
void RequestC2GGetSpecialTaskData(ClientNode* Client, BYTE* Body, size_t BodyLen); //231
void ResponseC2GGetSpecialTaskData(ClientNode* Client); //231
void RequestC2GUpdateSpecialTaskProgress(ClientNode* Client, BYTE* Body, size_t BodyLen); //232
void ResponseC2GUpdateSpecialTaskProgress(ClientNode* Client); //232
void NotifyFizzStarTaskComplete(ClientNode* Client); //11598
void NotifyUpdateGuildScore(ClientNode* Client); //12041
void RequestUseSpecialProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //11636
void ResponseUseSpecialProp(ClientNode* Client); //11636
void NotifyUseSpecialProp(ClientNode* Client); //11637
void NotifyCrazyPropAchieve(ClientNode* Client); //11638
void NotifyMusicBlackList(ClientNode* Client); //952
void NotifyPopularityChange(ClientNode* Client); //1701
void NotifyPlayerUpdateLadderMatchInfo(ClientNode* Client); //13050
void NotifyFreeForbiddenMode(ClientNode* Client); //13064
void RequestEnterWonderLandMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //866
void ResponseEnterWonderLandMap(ClientNode* Client); //866
void RequestExitWonderLandMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //867
void ResponseExitWonderLandMap(ClientNode* Client); //867
void NotifyEnterViewList(ClientNode* Client); //869
void NotifyLeaveViewList(ClientNode* Client); //870
void NotifyClearViewList(ClientNode* Client); //871
void NotifyPlayerListOfEnterWlCity(ClientNode* Client); //872
void NotifyPlayerListOfExitWlCity(ClientNode* Client); //873
void RequestWonderLandInnerToplist(ClientNode* Client, BYTE* Body, size_t BodyLen); //977
void ResponseWonderLandInnerToplist(ClientNode* Client); //977
void RequestC2GCreateWonderLand(ClientNode* Client, BYTE* Body, size_t BodyLen); //881
void ResponseC2GCreateWonderLand(ClientNode* Client); //881
void NotifyC2GCreateWonderLandResult(ClientNode* Client); //882
void NotifyC2GBriefWonderLandInfo(ClientNode* Client); //880
void RequestGetWonderLandGameSvrInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //889
void ResponseGetWonderLandGameSvrInfo(ClientNode* Client); //889
void RequestC2GApplyJoinWonderLand(ClientNode* Client, BYTE* Body, size_t BodyLen); //883
void ResponseC2GApplyJoinWonderLand(ClientNode* Client); //883
void NotifyC2GApplyJoinWonderLand(ClientNode* Client); //884
void RequestC2GReplyJoinWonderLand(ClientNode* Client, BYTE* Body, size_t BodyLen); //885
void ResponseC2GReplyJoinWonderLand(ClientNode* Client); //885
void NotifyAddToWonderLandResult(ClientNode* Client); //886
void RequestC2GWonderLandDetail(ClientNode* Client, BYTE* Body, size_t BodyLen); //887
void ResponseC2GWonderLandDetail(ClientNode* Client); //887
void RequestC2GWonderLandGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //888
void ResponseC2GWonderLandGuildInfo(ClientNode* Client); //888
void RequestC2GRemoveWonderlandGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //890
void ResponseC2GRemoveWonderlandGuild(ClientNode* Client); //890
void NotifyG2CRemoveWonderlandGuild(ClientNode* Client); //891
void NotifyG2CRemoveWonderlandPlayer(ClientNode* Client); //?
void RequestC2GCheckWonderLandName(ClientNode* Client, BYTE* Body, size_t BodyLen); //895
void ResponseC2GCheckWonderLandName(ClientNode* Client); //895
void RequestC2GFindWonderland(ClientNode* Client, BYTE* Body, size_t BodyLen); //896
void ResponseC2GFindWonderland(ClientNode* Client); //896
void RequestC2GFindWonderLandGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //919
void ResponseC2GFindWonderLandGuildInfo(ClientNode* Client); //919
void RequestC2GGetWonderlandList(ClientNode* Client, BYTE* Body, size_t BodyLen); //897
void ResponseC2GGetWonderlandList(ClientNode* Client); //897
void RequestC2GGetWonderlandSummaryInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //898
void ResponseC2GGetWonderlandSummaryInfo(ClientNode* Client); //898
void RequestC2GChangeWonderlandPlayerDuty(ClientNode* Client, BYTE* Body, size_t BodyLen); //893
void ResponseC2GChangeWonderlandPlayerDuty(ClientNode* Client); //893
void NotifyG2CChangeWonderlandPlayerDuty(ClientNode* Client); //894
void RequestC2GModifyWonderlandDutyRight(ClientNode* Client, BYTE* Body, size_t BodyLen); //925
void ResponseC2GModifyWonderlandDutyRight(ClientNode* Client); //925
void NotifyC2GModifyWonderlandDutyRight(ClientNode* Client); //937
void RequestC2GModifyWonderlandRecruitSetting(ClientNode* Client, BYTE* Body, size_t BodyLen); //926
void ResponseC2GModifyWonderlandRecruitSetting(ClientNode* Client); //926
void RequestC2GModifyWonderlandAttri(ClientNode* Client, BYTE* Body, size_t BodyLen); //927
void ResponseC2GModifyWonderlandAttri(ClientNode* Client); //927
void RequestC2GModifyWonderlandNotes(ClientNode* Client, BYTE* Body, size_t BodyLen); //928
void ResponseC2GModifyWonderlandNotes(ClientNode* Client); //928
void RequestC2GModifyWonderlandDescs(ClientNode* Client, BYTE* Body, size_t BodyLen); //929
void ResponseC2GModifyWonderlandDescs(ClientNode* Client); //929
void RequestC2GModifyGuildPlayerFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GModifyGuildPlayerFlag(ClientNode* Client); //?
void RequestC2GGetWLMstInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //938
void ResponseC2GGetWLMstInfo(ClientNode* Client); //938
void NotifyC2GUpdateWLMstInfo(ClientNode* Client); //939
void RequestC2GCheckNameDirty(ClientNode* Client, BYTE* Body, size_t BodyLen); //940
void ResponseC2GCheckNameDirty(ClientNode* Client); //940
void RequestC2GChangeWLMstName(ClientNode* Client, BYTE* Body, size_t BodyLen); //960
void ResponseC2GChangeWLMstName(ClientNode* Client); //960
void RequestC2GInitWLMonsterEgg(ClientNode* Client, BYTE* Body, size_t BodyLen); //953
void ResponseC2GInitWLMonsterEgg(ClientNode* Client); //953
void NotifyC2GInitWLMonsterEgg(ClientNode* Client); //954
void RequestC2GEvolutionWLMst(ClientNode* Client, BYTE* Body, size_t BodyLen); //955
void ResponseC2GEvolutionWLMst(ClientNode* Client); //955
void NotifyC2GEvolutionWLMst(ClientNode* Client); //956
void NotifyC2GEvolutionWLMstFinish(ClientNode* Client); //957
void RequestC2GFeedWLMst(ClientNode* Client, BYTE* Body, size_t BodyLen); //958
void ResponseC2GFeedWLMst(ClientNode* Client); //958
void RequestC2GCareWLMst(ClientNode* Client, BYTE* Body, size_t BodyLen); //959
void ResponseC2GCareWLMst(ClientNode* Client); //959
void RequestDonateEnergyMstEvolution(ClientNode* Client, BYTE* Body, size_t BodyLen); //966
void ResponseDonateEnergyMstEvolution(ClientNode* Client); //966
void RequestPickRoomGenItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //967
void ResponsePickRoomGenItem(ClientNode* Client); //967
void NotifyPickRoomGenItem(ClientNode* Client); //968
void NotifyRoomGenItem(ClientNode* Client); //969
void RequestC2GUpdateWlMstFlag(ClientNode* Client, BYTE* Body, size_t BodyLen); //974
void ResponseC2GUpdateWlMstFlag(ClientNode* Client); //974
void NotifyC2GUpdateWlMstFlag(ClientNode* Client); //975
void RequestGetWonderLandBuildingInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //899
void ResponseGetWonderLandBuildingInfo(ClientNode* Client); //899
void RequestUpgradeWonderLandBuilding(ClientNode* Client, BYTE* Body, size_t BodyLen); //915
void ResponseUpgradeWonderLandBuilding(ClientNode* Client); //915
void RequestDonateEnergy(ClientNode* Client, BYTE* Body, size_t BodyLen); //916
void ResponseDonateEnergy(ClientNode* Client); //916
void NotifyUpgradeWonderLandBuildingFinished(ClientNode* Client); //917
void RequestSetWonderLandBuildingAttribute(ClientNode* Client, BYTE* Body, size_t BodyLen); //918
void ResponseSetWonderLandBuildingAttribute(ClientNode* Client); //918
void NotifyUpdateWlBuilding(ClientNode* Client); //914
void NotifyClientWlCapacityChanage(ClientNode* Client); //979
void RequestC2GGetRecommendWLList(ClientNode* Client, BYTE* Body, size_t BodyLen); //983
void ResponseC2GGetRecommendWLList(ClientNode* Client); //983
void RequestC2GGetRecommendWlGuildList(ClientNode* Client, BYTE* Body, size_t BodyLen); //984
void ResponseC2GGetRecommendWlGuildList(ClientNode* Client); //984
void RequestGetRecommendWlCityList(ClientNode* Client, BYTE* Body, size_t BodyLen); //991
void ResponseGetRecommendWlCityList(ClientNode* Client); //991
void RequestBanWlTalk(ClientNode* Client, BYTE* Body, size_t BodyLen); //992
void ResponseBanWlTalk(ClientNode* Client); //992
void RequestQueryWlWelfareInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //990
void ResponseQueryWlWelfareInfo(ClientNode* Client); //990
void RequestGetWlWelfare(ClientNode* Client, BYTE* Body, size_t BodyLen); //985
void ResponseGetWlWelfare(ClientNode* Client); //985
void RequestQueryWlBonusInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //986
void ResponseQueryWlBonusInfo(ClientNode* Client); //986
void RequestStartWlBonus(ClientNode* Client, BYTE* Body, size_t BodyLen); //987
void ResponseStartWlBonus(ClientNode* Client); //987
void RequestGetWlBonus(ClientNode* Client, BYTE* Body, size_t BodyLen); //988
void ResponseGetWlBonus(ClientNode* Client); //988
void RequestKickFromWlRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //874
void ResponseKickFromWlRoom(ClientNode* Client); //874
void NotifyKickFromWlRoom(ClientNode* Client); //875
void RequestGuildDonate(ClientNode* Client, BYTE* Body, size_t BodyLen); //997
void ResponseGuildDonate(ClientNode* Client); //997
void NotifyGS2CUserVisionOnNPC(ClientNode* Client); //13001
void NotifyGS2CUpdateNPCAttr(ClientNode* Client); //13002
void RequestGSUserActOnNPC(ClientNode* Client, BYTE* Body, size_t BodyLen); //13003
void ResponseGSUserActOnNPC(ClientNode* Client); //13003
void NotifyGS2CUserActOnNPC(ClientNode* Client); //13004
void NotifyGS2CUserActionResult(ClientNode* Client); //13005
void NotifyGS2CCatchTraitorSettle(ClientNode* Client); //13006
void RequestGSGetCatchTraitorInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //13107
void ResponseGSGetCatchTraitorInfo(ClientNode* Client); //13107
void ResponseGSBeginCatchTraitor(ClientNode* Client); //13007
void RequestUserApplyInMaze(ClientNode* Client, BYTE* Body, size_t BodyLen); //13008
void ResponseUserApplyInMaze(ClientNode* Client); //13008
void RequestUserApplyOutMaze(ClientNode* Client, BYTE* Body, size_t BodyLen); //13009
void ResponseUserApplyOutMaze(ClientNode* Client); //13009
void NotifyUserOutMaze(ClientNode* Client); //13106
void NotifyWlNpcMove(ClientNode* Client); //13108
void NotifyWlNpcAttackPlayer(ClientNode* Client); //13109
void NotifyAttackBeastSettle(ClientNode* Client); //13114
void NotifyWlNpcCarryCoupons(ClientNode* Client); //13116
void RequestC2GGetWlQTRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //980
void ResponseC2GGetWlQTRoomList(ClientNode* Client); //980
void RequestC2GCreateWlQTRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //981
void ResponseC2GCreateWlQTRoom(ClientNode* Client); //981
void RequestC2GSetWlQTRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //982
void ResponseC2GSetWlQTRoom(ClientNode* Client); //982
void ResponseWishTreeInfo(ClientNode* Client); //12196
void ResponseWishTreeWater(ClientNode* Client); //12197
void ResponseWishTreeBuyCommodity(ClientNode* Client); //12198
void NotifyWishTreeBaseInfoChangeInfo(ClientNode* Client); //12199
void RequestC2SSearchKartAltas(ClientNode* Client, BYTE* Body, size_t BodyLen); //13705
void ResponseC2SearchKartAltas(ClientNode* Client); //13705
void NotifyS2CMyKartAltas(ClientNode* Client); //13706
void RequestC2SGetKartAltasConfig(ClientNode* Client, BYTE* Body, size_t BodyLen); //13710
void ResponseC2SGetKartAltasConfig(ClientNode* Client); //13710
void RequestC2STakePartInCarnival(ClientNode* Client, BYTE* Body, size_t BodyLen); //13077
void ResponseC2STakePartInCarnival(ClientNode* Client); //13077
void NotifySMCCarnivalGameResult(ClientNode* Client); //13080
void RequestPointCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //13711
void ResponsePointCfg(ClientNode* Client); //13711
void RequestPointChallengeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //13712
void ResponsePointChallengeInfo(ClientNode* Client); //13712
void RequestStartPointChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //13713
void ResponseStartPointChallenge(ClientNode* Client); //13713
void NotifyPointChallengeResult(ClientNode* Client); //13714
void RequestQuitPointChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //13715
void RequestReportRoomChat(ClientNode* Client, BYTE* Body, size_t BodyLen); //13720
void NotifyFirstRechargeCfg(ClientNode* Client); //13722
void RequestFirstRechargeAarwd(ClientNode* Client, BYTE* Body, size_t BodyLen); //13721
void ResponseFirstRechargeAward(ClientNode* Client); //13721
void NotifyClientUpdateLoverVipInfo(ClientNode* Client); //13800
void NotifyClientLoverVipExpireInfo(ClientNode* Client); //13801
void RequestReceiveLoverVipGift(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveLoverVipGift(ClientNode* Client); //13802
void RequestRefreshLoverTarotAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRefreshLoverTarotAward(ClientNode* Client); //13803
void RequestGetLoverTarotAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLoverTarotAward(ClientNode* Client); //13804
void RequestGetLoverTarotBroadcast(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLoverTarotBroadcast(ClientNode* Client); //13805
void RequestGetControlItemInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetControlItemInfo(ClientNode* Client); //?
void RequestAddItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAddItem(ClientNode* Client); //?
void RequestGetNextGuessFigureQuestion(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNextGuessFigureQuestion(ClientNode* Client); //20011
void RequestAnswerGuessFigureQuestion(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAnswerGuessFigureQuestion(ClientNode* Client); //20012
void RequestGetHelpForGuessFigureQuestion(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetHelpForGuessFigureQuestion(ClientNode* Client); //20013
void NotifyGetHelpForGuessFigureQuestion(ClientNode* Client); //20014
void NotifyShareGuessFigureQuestionAnswer(ClientNode* Client); //?
void AckShareGuessFigureQuestionAnswer(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyS2CGodFortuneStatus(ClientNode* Client); //20025
void NotifyS2CGodFortunePackage(ClientNode* Client); //20026
void RequestC2SPickUpFortunePac(ClientNode* Client, BYTE* Body, size_t BodyLen); //20027
void ResponseC2SPickUpFortunePac(ClientNode* Client); //20027
void NotifyS2CPackageBeenPickUp(ClientNode* Client); //20028
void NotifyS2CEnterGodFortuneActivity(ClientNode* Client); //20029
void NotifyClientTips(ClientNode* Client); //20030
void RequestClientReportDataMinintLog(ClientNode* Client, BYTE* Body, size_t BodyLen); //20031
void RequestGetBattleModeCarSkillInfoList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBattleModeCarSkillInfoList(ClientNode* Client); //10929
void RequestGetBattleModeRoleSkillInfoList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBattleModeRoleSkillInfoList(ClientNode* Client); //10930
void RequestSkillStrengthenBattleModeCar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkillStrengthenBattleModeCar(ClientNode* Client); //10931
void RequestSkillStrengthenBattleModeRole(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkillStrengthenBattleModeRole(ClientNode* Client); //10932
void RequestC2GGetBattleModeConfig(ClientNode* Client, BYTE* Body, size_t BodyLen); //10933
void ResponseC2GGetBattleModeConfig(ClientNode* Client); //10933
void RequestC2GGetBattleModeScoreList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetBattleModeScoreList(ClientNode* Client); //10934
void RequestC2SReceiveTimesExperience(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2SReceiveTimesExperience(ClientNode* Client); //20040
void RequestC2SFrostThawTimesExperience(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2SFrostThawTimesExperience(ClientNode* Client); //20041
void RequestC2SGetTimesExperienceInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2SGetTimesExperienceInfo(ClientNode* Client); //20042
void RequestC2SUpdateDayUpgradeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2SUpdateDayUpgradeInfo(ClientNode* Client); //?
void NotifyClientPop(ClientNode* Client); //20045
void RequestRedPacketPresentInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRedPacketPresentInfo(ClientNode* Client); //20046
void RequestPresentFriendRedPacket(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePresentFriendRedPacket(ClientNode* Client); //20047
void NotifyReduceCouponsDayConsumeInfo(ClientNode* Client); //20050
void NotifyFBMonsterRefresh(ClientNode* Client); //20070
void RequestFBReportMonsterEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //20071
void NotifyFBScoreEvent(ClientNode* Client); //20073
void NotifyFBUpdateMonsterInfo(ClientNode* Client); //20072
void RequestFBReportCurrentCP(ClientNode* Client, BYTE* Body, size_t BodyLen); //20074
void RequestGetRecommendItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //20075
void ResponseGetRecommendItemList(ClientNode* Client); //20075
void RequestCanGetRecommendItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //20076
void ResponseCanGetRecommendItemList(ClientNode* Client); //20076
void NotifyTaskPresentAward(ClientNode* Client); //20048
void RequestSaveDataForPresent(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSaveDataForPresent(ClientNode* Client); //20049
void RequestAddToMatchQueue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAddToMatchQueue(ClientNode* Client); //20079
void RequestCancelMatchQueue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelMatchQueue(ClientNode* Client); //20080
void NotifyMatchResult(ClientNode* Client); //20081
void RequestEnterMatchRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseEnterMatchRoom(ClientNode* Client); //20082
void RequestGetBorderGameCondition(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyFBPlayerLevInfo(ClientNode* Client); //20069
void NotifyPetStrengCfgInfo(ClientNode* Client); //20100
void RequestPetStrengthen(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePetStrengthen(ClientNode* Client); //20101
void NotifyMapMedalInfo(ClientNode* Client); //20084
void NotifyUpdateMapMedalInfo(ClientNode* Client); //20085
void RequestGetMapMedalCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //20086
void ResponseGetMapMedalCfg(ClientNode* Client); //20086
void NotifyClearMapMedalAllInfo(ClientNode* Client); //20087
void RequestGetVipLv7Item(ClientNode* Client, BYTE* Body, size_t BodyLen); //20102
void ResponseGetVipLv7Item(ClientNode* Client); //20102
void RequestReportCommonAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //20097
