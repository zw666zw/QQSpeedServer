void RequestGetPurchaseBroadcast(ClientNode* Client, BYTE* Body, size_t BodyLen); //20007
void ResponseGetPurchaseBroadcast(ClientNode* Client); //20007
void RequestCheckCommodityOnSale(ClientNode* Client, BYTE* Body, size_t BodyLen); //20006
void ResponseCheckCommodityOnSale(ClientNode* Client); //20006
void RequestBuyCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen); //20000
void ResponseBuyCommodity(ClientNode* Client); //20000
void RequestBuyCommodityEx(ClientNode* Client, BYTE* Body, size_t BodyLen); //20005
void ResponseBuyCommodityEx(ClientNode* Client); //20005
void RequestBuyActivity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyActivity(ClientNode* Client); //19999
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
void RequestWebpaySendItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWebpaySendItem(ClientNode* Client); //?
void NotifyShowWebPayPage(ClientNode* Client); //24813
void RequestPayRebateCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //20077
void ResponsePayRebateCfg(ClientNode* Client); //20077
void RequestReduceCouponseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20051
void ResponseReduceCouponseInfo(ClientNode* Client); //20051
void RequestCashCouponseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20052
void ResponseCashCouponseInfo(ClientNode* Client); //20052
void RequestPurchaseLimitCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //21100
void ResponsePurchaseLimitCfg(ClientNode* Client); //21100
void NotifyUpdatePurchaseLimitInfo(ClientNode* Client); //21101
void RequestS2APrevUseNum(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyS2APostUseNum(ClientNode* Client); //?
void ResponseS2APrevUseNum(ClientNode* Client); //?
void RequestGetWorldInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //90
void ResponseGetWorldInfo(ClientNode* Client); //90
void RequestGetChatAreaList(ClientNode* Client, BYTE* Body, size_t BodyLen); //85
void ResponseGetChatAreaList(ClientNode* Client); //85
void RequestGetChatRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //91
void ResponseGetChatRoomList(ClientNode* Client); //91
void RequestC2FUpLoad(ClientNode* Client, BYTE* Body, size_t BodyLen); //11200
void ResponseC2FUpLoad(ClientNode* Client); //11200
void NotifyRankedMatchBanMapInfo(ClientNode* Client); //25009
void RequestRankedMatchDoBanMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRankedMatchDoBanMap(ClientNode* Client); //25010
void NotifyRankedMatchBanMapResult(ClientNode* Client); //25011
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
void NotifyG2CLoverMatchRoomPlayerInfo(ClientNode* Client); //21222
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
void RequestC2LMGetOneTruthInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2LMGetOneTruthInfo(ClientNode* Client); //21221
void RequestC2GGetLoveMatchLotteryBroad(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetLoveMatchLotteryBroad(ClientNode* Client); //11343
void RequestC2GGetLoverMatchCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GGetLoverMatchCfg(ClientNode* Client); //11311
void NotifyG2CLoverMatchTopRaceStageInfo(ClientNode* Client); //11376
void NotifyG2CLoverMatchTopRaceAward(ClientNode* Client); //11377
void NotifyG2CLoverMatchTopRaceNextStageShow(ClientNode* Client); //11378
void RequestQueryIsInLoverMatchTime(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQueryIsInLoverMatchTime(ClientNode* Client); //11321
void RequestChangeLMTeamMateMatchMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeLMTeamMateMatchMode(ClientNode* Client); //11359
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
void RequestOpenSignBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpenSignBox(ClientNode* Client); //24041
void RequestC2GGetSign2Info(ClientNode* Client, BYTE* Body, size_t BodyLen); //1100
void ResponseC2GGetSign2Info(ClientNode* Client); //1100
void RequestC2GSign2(ClientNode* Client, BYTE* Body, size_t BodyLen); //1101
void ResponseC2GSign2(ClientNode* Client); //1101
void RequestC2GSign3Operate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2GSign3Operate(ClientNode* Client); //1401
void RequestPlayerTestMsg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePlayerTestMsg(ClientNode* Client); //?
void RequestRankedMatchArenaOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRankedMatchArenaOperate(ClientNode* Client); //1403
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
void NotifyForbiddenModeAnti(ClientNode* Client); //24757
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
void RequestGetPlayerItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //437
void ResponseGetPlayerItem(ClientNode* Client); //437
void NotifyLoginMoreItemInfo(ClientNode* Client); //438
void RequestGetLoginNotifyMsg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLoginNotifyMsg(ClientNode* Client); //439
void RequestReportConnectLog(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReportConnectLog(ClientNode* Client); //?
void NotifyReportConnectLog(ClientNode* Client); //?
void NotifyMaxItemNumExtended(ClientNode* Client); //11475
void NotifyLoginMoreInfo(ClientNode* Client); //223
void RequestLogout(ClientNode* Client, BYTE* Body, size_t BodyLen); //101
void ResponseLogout(ClientNode* Client); //101
void RequestGetRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen); //102
void NotifyClientUpdateGuildScoreInRoomInfo(ClientNode* Client); //12033
void ResponseGetRoomList(ClientNode* Client); //102
void RequestAddToTeamMatchQueue(ClientNode* Client, BYTE* Body, size_t BodyLen); //20210
void ResponsetAddToTeamMatchQueue(ClientNode* Client); //20210
void RequestCancelTeamMatchQueue(ClientNode* Client, BYTE* Body, size_t BodyLen); //20211
void ResponseCancelTeamMatchQueue(ClientNode* Client); //20211
void NotifyCancelTeamMatchQueue(ClientNode* Client); //20212
void NotifyAddToTeamMatchQueue(ClientNode* Client); //20213
void RequestChangeTeamMatchMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeTeamMatchMode(ClientNode* Client); //20214
void RequestCreateRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //103
void ResponseCreateRoom(ClientNode* Client); //103
void RequestEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //104
void NotifyEnterRoomMoreInfo(ClientNode* Client); //224
void NotifyEnterRoom(ClientNode* Client); //500
void RequestLeaveRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //105
void ResponseLeaveRoom(ClientNode* Client); //105
void NotifyLeaveRoom(ClientNode* Client); //501
void RequestLeaveGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLeaveGame(ClientNode* Client); //424
void RequestDeleteRole(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDeleteRole(ClientNode* Client); //425
void NotifyChangeRoomOwner(ClientNode* Client); //524
void RequestChangeRoomOwner(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeRoomOwner(ClientNode* Client); //713
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
void RequestForbidFromRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //243
void ResponseForbidFromRoom(ClientNode* Client); //243
void NotifyForbidFromRoom(ClientNode* Client); //632
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
void NotifyKickFromGame(ClientNode* Client); //460
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
void NotifyCheckPointTimeDiff(ClientNode* Client); //274
void RequestPrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen); //120
void NotifyWaitUnReadyPlayers(ClientNode* Client); //510
void NotifyGameNPCInfo(ClientNode* Client); //784
void NotifyRaceBegin(ClientNode* Client); //511
void NotifyCountDown(ClientNode* Client); //512
void NotifyGameStatus(ClientNode* Client); //786
void NotifyStageOver(ClientNode* Client); //785
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
void NotifyFriendInfo(ClientNode* Client); //633
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
void RequestGetBoxCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBoxCfg(ClientNode* Client); //299
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
void NotifyBorderPlayerMoreInfo(ClientNode* Client); //620
void RequestCountryHonor(ClientNode* Client, BYTE* Body, size_t BodyLen); //146
void ResponseCountryHonor(ClientNode* Client); //146
void RequestUpdatePlayerPos(ClientNode* Client, BYTE* Body, size_t BodyLen); //457
void NotifyBroadcastPlayerPos(ClientNode* Client); //458
void RequestEnterOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen); //352
void ResponseEnterOutdoor(ClientNode* Client); //352
void NotifyChatGameBegin(ClientNode* Client); //454
void NotifyChatGameLeaveGame(ClientNode* Client); //455
void NotifyChatGameOver(ClientNode* Client); //456
void NotifyEnterOutdoor(ClientNode* Client); //852
void RequestChangeHammerStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //359
void ResponseChangeHammerStatus(ClientNode* Client); //359
void NotifyChangeHammerStatus(ClientNode* Client); //861
void RequestChangeSuperShoeStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //24428
void ResponseChangeSuperShoeStatus(ClientNode* Client); //24428
void NotifyChangeSuperShoeStatus(ClientNode* Client); //24427
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
void NotifyMatchPlayerMoreInfo(ClientNode* Client); //619
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
void NotifyWlMatchPlayerMoreInfo(ClientNode* Client); //618
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
void ResponseReplyJoinGuild(ClientNode* Client); //15013
void RequestRemoveMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //15002
void ResponseRemoveMember(ClientNode* Client); //15002
void NotifyRemoveMember(ClientNode* Client); //15202
void RequestGetGuildList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15004
void ResponseGetGuildList(ClientNode* Client); //15004
void RequestFindGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //15009
void ResponseFindGuild(ClientNode* Client); //15009
void RequestGuildDetail(ClientNode* Client, BYTE* Body, size_t BodyLen); //15003
void ResponseGuildDetail(ClientNode* Client); //15003
void RequestGuildNotes(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildNotes(ClientNode* Client); //24309
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
void RequestTransferPropEffect(ClientNode* Client, BYTE* Body, size_t BodyLen); //203
void NotifyTransferPropEffect(ClientNode* Client); //204
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
void NotifySkillStoneKartMoreInfo(ClientNode* Client); //28416
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
void NotifyTimerChallengeChangeBuffStatus(ClientNode* Client); //28422
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
void RequestLmtBuglet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsetLmtBuglet(ClientNode* Client); //812
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
void ResponseGetWareHouseItemListMoreInfo(ClientNode* Client); //429
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
void NotifySvrConfig2MoreInfo(ClientNode* Client); //823
void NotifySvrConfig3(ClientNode* Client); //25066
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
void ResponseKartRefitInfoMoreInfo(ClientNode* Client); //318
void RequestShapeRefit(ClientNode* Client, BYTE* Body, size_t BodyLen); //272
void ResponseShapeRefit(ClientNode* Client); //272
void RequestSaveShapeRefit(ClientNode* Client, BYTE* Body, size_t BodyLen); //316
void ResponseSaveShapeRefit(ClientNode* Client); //316
void RequestGetShapeRefitCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //317
void ResponseGetShapeRefitCfg(ClientNode* Client); //317
void RequestShapeLegendOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //319
void ResponseShapeLegendOperate(ClientNode* Client); //319
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
void NotifyClientUpdateEmperorInfo(ClientNode* Client); //978
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
void ResponseC2SearchKartAltasMoreInfo(ClientNode* Client); //13703
void NotifyS2CMyKartAltas(ClientNode* Client); //13706
void NotifyS2CMyKartAltasMoreInfo(ClientNode* Client); //13704
void RequestC2SGetKartAltasConfig(ClientNode* Client, BYTE* Body, size_t BodyLen); //13710
void ResponseC2SGetKartAltasConfig(ClientNode* Client); //13710
void RequestC2STakePartInCarnival(ClientNode* Client, BYTE* Body, size_t BodyLen); //13077
void ResponseC2STakePartInCarnival(ClientNode* Client); //13077
void NotifySMCCarnivalGameResult(ClientNode* Client); //13080
void RequestPointCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //13711
void ResponsePointCfg(ClientNode* Client); //13711
void ResponsePointCfgMoreInfo(ClientNode* Client); //13763
void RequestPointChallengeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //13712
void ResponsePointChallengeInfo(ClientNode* Client); //13712
void RequestPointChallengeChooseCar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeChooseCar(ClientNode* Client); //28232
void RequestStartPointChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //13713
void ResponseStartPointChallenge(ClientNode* Client); //13713
void NotifyPointChallengeResult(ClientNode* Client); //13714
void RequestQuitPointChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //13715
void RequestSelectPoint(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSelectPoint(ClientNode* Client); //13764
void RequestReSelectOnePoint(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReSelectOnePoint(ClientNode* Client); //13765
void RequestGetOneFragment(ClientNode* Client, BYTE* Body, size_t BodyLen); //13766
void ResponseGetOneFragment(ClientNode* Client); //13766
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
void RequestGetPetShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24426
void ResponseGetPetShowInfo(ClientNode* Client); //24426
void ResponseGetPetShowMoreInfo(ClientNode* Client); //24527
void RequestGetPetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24528
void ResponseGetPetInfo(ClientNode* Client); //24528
void NotifyPetStrengCfgInfo(ClientNode* Client); //20100
void NotifyPetStrengCfgMoreInfo(ClientNode* Client); //28228
void NotifyPetStrengPetID(ClientNode* Client); //24074
void NotifyPetHuanHuaCfgInfo(ClientNode* Client); //24073
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
void NotifyAvatarSynthesisCfg(ClientNode* Client); //20103
void RequestAvatarSynthesize(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAvatarSynthesize(ClientNode* Client); //20104
void RequestAvatarAdvance(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAvatarAdvance(ClientNode* Client); //20105
void NotifyLingShouResultToKeeper(ClientNode* Client); //13117
void NotifyLingShouResultToIntruder(ClientNode* Client); //13118
void RequestVipDetailInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20106
void ResponseVipDetailInfo(ClientNode* Client); //20106
void RequestReportPlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReportPlayer(ClientNode* Client); //20107
void RequestGet2048AwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGet2048AwardInfo(ClientNode* Client); //13119
void RequestReport2048Result(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReport2048Result(ClientNode* Client); //13122
void NotifyServerLog(ClientNode* Client); //?
void NotifyG2CChumCircleBriefInfo(ClientNode* Client); //15400
void RequestGetChumCircleDetailInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //15401
void ResponseGetChumCircleDetailInfo(ClientNode* Client); //15401
void RequestCreateChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15402
void ResponseCreateChumCircle(ClientNode* Client); //15402
void NotifyInvitedCreateChumCircle(ClientNode* Client); //15403
void RequestReplyInviteCreateChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15404
void ResponseReplyInviteCreateChumCircle(ClientNode* Client); //15404
void NotifyReplyInviteCreateChumCircle(ClientNode* Client); //15405
void NotifyCreateChumCircleResult(ClientNode* Client); //15406
void RequestInviteJoinChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15407
void ResponseInviteJoinChumCircle(ClientNode* Client); //15407
void NotifyInviteJoinChumCircle(ClientNode* Client); //15408
void RequestReplyInviteJoinChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15409
void ResponseReplyInviteJoinChumCircle(ClientNode* Client); //15409
void NotifyReplyInviteJoinChumCircle(ClientNode* Client); //15410
void NotifyJoinChumCircleResult(ClientNode* Client); //15411
void RequestApplyJoinChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15423
void ResponseApplyJoinChumCircle(ClientNode* Client); //15423
void NotifyApplyJoinChumCircle(ClientNode* Client); //15424
void RequestReplyApplyJoinChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15425
void ResponseReplyApplyJoinChumCircle(ClientNode* Client); //15425
void NotifyReplyApplyJoinChumCircle(ClientNode* Client); //15426
void RequestRemoveChumCircleMember(ClientNode* Client, BYTE* Body, size_t BodyLen); //15412
void ResponseRemoveChumCircleMember(ClientNode* Client); //15412
void NotifyRemoveChumCircleMember(ClientNode* Client); //15413
void RequestChangeChumCircleDuty(ClientNode* Client, BYTE* Body, size_t BodyLen); //15414
void ResponseChangeChumCircleDuty(ClientNode* Client); //15414
void NotifyChangeChumCircleDuty(ClientNode* Client); //15415
void RequestCheckChumCircleName(ClientNode* Client, BYTE* Body, size_t BodyLen); //15416
void ResponseCheckChumCircleName(ClientNode* Client); //15416
void RequestInviteJoinChumCircleFriendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15417
void ResponseInviteJoinChumCircleFriendList(ClientNode* Client); //15417
void RequestGetFriendChumCircleRecommendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //15421
void ResponseGetFriendChumCircleRecommendList(ClientNode* Client); //15421
void NotifyFriendChumCircleRecommendDetail(ClientNode* Client); //15422
void RequestExpandChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //15418
void ResponseExpandChumCircle(ClientNode* Client); //15418
void RequestSetChumCircleNickName(ClientNode* Client, BYTE* Body, size_t BodyLen); //15419
void ResponseSetChumCircleNickName(ClientNode* Client); //15419
void RequestGetChumCircleNickName(ClientNode* Client, BYTE* Body, size_t BodyLen); //15420
void ResponseGetChumCircleNickName(ClientNode* Client); //15420
void NotifyChumCircleSkillActivited(ClientNode* Client); //21005
void RequestReportChumCircleSkillActive(ClientNode* Client, BYTE* Body, size_t BodyLen); //21004
void RequestDonateChumCircleEnergy(ClientNode* Client, BYTE* Body, size_t BodyLen); //21003
void ResponseDonateChumCircleEnergy(ClientNode* Client); //21003
void RequestUpgradeChumCircle(ClientNode* Client, BYTE* Body, size_t BodyLen); //21002
void ResponseUpgradeChumCircle(ClientNode* Client); //21002
void NotifyChumCircleChangeInfo(ClientNode* Client); //21006
void NotifyChumCirclePlayerChangeInfo(ClientNode* Client); //21007
void NotifyChumCircleCfg(ClientNode* Client); //21001
void RequestGoInHand(ClientNode* Client, BYTE* Body, size_t BodyLen); //20109
void ResponseGoInHand(ClientNode* Client); //20109
void NotifyPlayerAcceptInHand(ClientNode* Client); //20110
void RequestAcceptInHand(ClientNode* Client, BYTE* Body, size_t BodyLen); //20111
void ResponseAcceptInHand(ClientNode* Client); //20111
void NotifyInHandResult(ClientNode* Client); //20112
void RequestReportQTEValue(ClientNode* Client, BYTE* Body, size_t BodyLen); //20113
void ResponseReportQTEValue(ClientNode* Client); //20113
void NotifyInHandEnd(ClientNode* Client); //20114
void NotifyPlayerAllowInvite(ClientNode* Client); //20115
void NotifyPlayerQTEResult(ClientNode* Client); //20116
void NotifySkateLoveAdd(ClientNode* Client); //20117
void RequestReportClientAntibotData(ClientNode* Client, BYTE* Body, size_t BodyLen); //15399
void RequestChangePetEquipStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangePetEquipStatus(ClientNode* Client); //15398
void RequestGetPlayerNonSaleItemInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20125
void ResponseGetPlayerNonSaleItemInfo(ClientNode* Client); //20125
void RequestGetShopNonSaleInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20126
void ResponseGetShopNonSaleInfo(ClientNode* Client); //20126
void RequestFocusNonSaleItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //20127
void ResponseFocusNonSaleItem(ClientNode* Client); //20127
void RequestGetNonSaleItemConsumeItemList(ClientNode* Client, BYTE* Body, size_t BodyLen); //20128
void ResponseGetNonSaleItemConsumeItemList(ClientNode* Client); //20128
void NotifyPlayerNoSaleProduceList(ClientNode* Client); //20129
void NotifyCompetitionSystemConfig(ClientNode* Client); //20133
void RequestShuttleGetProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //20134
void ResponseShuttleGetProp(ClientNode* Client); //20134
void RequestShuttleChangleMapMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //20135
void ResponseShuttleChangleMapMode(ClientNode* Client); //20135
void NotifyShuttleChangleMapMode(ClientNode* Client); //20136
void RequestEnterPersonalGarden(ClientNode* Client, BYTE* Body, size_t BodyLen); //20137
void ResponseEnterPersonalGarden(ClientNode* Client); //20137
void RequestUnlockParkingLot(ClientNode* Client, BYTE* Body, size_t BodyLen); //20139
void ResponseUnlockParkingLot(ClientNode* Client); //20139
void RequestPersonalGardenParking(ClientNode* Client, BYTE* Body, size_t BodyLen); //20140
void ResponsePersonalGardenParking(ClientNode* Client); //20140
void RequestGetParkingAwards(ClientNode* Client, BYTE* Body, size_t BodyLen); //20141
void ResponseGetParkingAwards(ClientNode* Client); //20141
void RequestUnlockStockingLot(ClientNode* Client, BYTE* Body, size_t BodyLen); //20143
void ResponseUnlockStockingLot(ClientNode* Client); //20143
void RequestPersonalGardenStocking(ClientNode* Client, BYTE* Body, size_t BodyLen); //20144
void ResponsePersonalGardenStocking(ClientNode* Client); //20144
void NotifyChangeStockingStatus(ClientNode* Client); //20147
void NotifyClientPersonalGardenCfg(ClientNode* Client); //20145
void NotifyClientChangeParkingInfo(ClientNode* Client); //20148
void RequestGetGardenParkingMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //20149
void ResponseGetGardenParkingMap(ClientNode* Client); //20149
void RequestGetBatchPlayerGardenInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20146
void ResponseGetBatchPlayerGardenInfo(ClientNode* Client); //20146
void RequestC2GGetGardenActivityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //20150
void ResponseC2GGetGardenActivityInfo(ClientNode* Client); //20150
void RequestChangeGardenRight(ClientNode* Client, BYTE* Body, size_t BodyLen); //20151
void ResponseChangeGardenRight(ClientNode* Client); //20151
void RequestUpgradeGardenBuildingLevel(ClientNode* Client, BYTE* Body, size_t BodyLen); //20153
void ResponseUpgradeGardenBuildingLevel(ClientNode* Client); //20153
void RequestGetGardenRecommendList(ClientNode* Client, BYTE* Body, size_t BodyLen); //20152
void ResponseGetGardenRecommendList(ClientNode* Client); //20152
void NotifyClientUpdatePersonalGardenBaseInfo(ClientNode* Client); //20301
void RequestChangeRubberDuckState(ClientNode* Client, BYTE* Body, size_t BodyLen); //20154
void ResponseChangeRubberDuckState(ClientNode* Client); //20154
void NotifyChangeRubberDuckState(ClientNode* Client); //20155
void NotifySnowFrozenTimeInfo(ClientNode* Client); //21013
void NotifyIceBegin(ClientNode* Client); //21010
void NotifyIceEndInfo(ClientNode* Client); //21012
void NotifyIceAllInfo(ClientNode* Client); //21011
void RequestGetIceBlock(ClientNode* Client, BYTE* Body, size_t BodyLen); //21008
void ResponseGetIceBlock(ClientNode* Client); //21008
void RequestUpIceBlock(ClientNode* Client, BYTE* Body, size_t BodyLen); //21009
void ResponseUpIceBlock(ClientNode* Client); //21009
void NotifyConsumeGiftBagInfo(ClientNode* Client); //24006
void RequestGetConsumeGiftBagAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24007
void ResponseGetConsumeGiftBagAward(ClientNode* Client); //24007
void NotifyConsumeCountChange(ClientNode* Client); //24008
void NotifyRelaxRoomAdvertisement(ClientNode* Client); //24009
void RequestGetSecondPassInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifySecondPassInfo(ClientNode* Client); //21015
void NotifySecondPassReClose(ClientNode* Client); //21016
void RequestOpSecondPass(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpSecondPass(ClientNode* Client); //21017
void NotifySecondPassOpNotAllowed(ClientNode* Client); //21018
void RequestGetGameBaseRecordList(ClientNode* Client, BYTE* Body, size_t BodyLen); //1702
void ResponseGetGameBaseRecordList(ClientNode* Client); //1702
void RequestGetGameDetailRecordList(ClientNode* Client, BYTE* Body, size_t BodyLen); //1703
void ResponseGetGameDetailRecordList(ClientNode* Client); //1703
void RequestGameDetailRecordCheatingReport(ClientNode* Client, BYTE* Body, size_t BodyLen); //1704
void RequestShuttleUserSelectMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseShuttleUserSelectMap(ClientNode* Client); //1705
void NotifyShuttleUserSelectMap(ClientNode* Client); //1706
void NotifyShuttleScoreWeek(ClientNode* Client); //1711
void NotifyWeeklyRecommendModeAward(ClientNode* Client); //1712
void RequestWeeklyRecommendModeTriggerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //1713
void NotifyDynamicCode(ClientNode* Client); //21032
void RequestGetRecommendTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //21033
void ResponseGetRecommendTask(ClientNode* Client); //21033
void RequestRecommendTaskChange(ClientNode* Client, BYTE* Body, size_t BodyLen); //21029
void ResponseRecommendTaskChange(ClientNode* Client); //21029
void RequestGetLottoryItemAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //1714
void ResponseGetLottoryItemAwardCfg(ClientNode* Client); //1714
void RequestUseLottoryItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //1715
void ResponseUseLottoryItem(ClientNode* Client); //1715
void RequestSecondRefitKart(ClientNode* Client, BYTE* Body, size_t BodyLen); //21110
void ResponseSecondRefitKart(ClientNode* Client); //21110
void RequestSecondGetKartRefitLimitCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //21111
void ResponseSecondGetKartRefitLimitCfg(ClientNode* Client); //21111
void RequestGetGuildOnlineAwardCoupons(ClientNode* Client, BYTE* Body, size_t BodyLen); //16049
void ResponseGetGuildOnlineAwardCoupons(ClientNode* Client); //16050
void RequestPlayerGuildRegister(ClientNode* Client, BYTE* Body, size_t BodyLen); //16043
void ResponsePlayerGuildRegister(ClientNode* Client); //16044
void RequestPlayerReceiveGuildAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //16045
void ResponsePlayerReceiveGuildAward(ClientNode* Client); //16046
void RequestUpdateGuildOnlineAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //16047
void ResponseUpdateGuildOnlineAward(ClientNode* Client); //16048
void NotifyDaLeDouEnergy(ClientNode* Client); //307
void RequestDaLeDouEnergyStrengthenProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //308
void ResponseDaLeDouEnergyStrengthenProp(ClientNode* Client); //308
void RequestDaLeDouSelectProp(ClientNode* Client, BYTE* Body, size_t BodyLen); //309
void ResponseDaLeDouSelectProp(ClientNode* Client); //309
void RequestDaLeDouSurpass(ClientNode* Client, BYTE* Body, size_t BodyLen); //311
void NotifyDaLeDouBuf(ClientNode* Client); //310
void RequestReportCurrentDistanceToEnd(ClientNode* Client, BYTE* Body, size_t BodyLen); //312
void NotifyRecommendRelation(ClientNode* Client); //21112
void RequestGetRecommendRelationItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRecommnedRelationItem(ClientNode* Client); //21113
void RequestBuyFinancialProduct(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyFinancialProduct(ClientNode* Client); //?
void RequestFinancialProductBuyStatInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFinancialProductBuyStatInfo(ClientNode* Client); //?
void NotifyFinancialProductBuyStatToClient(ClientNode* Client); //?
void RequestReceiveFinancialProductAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveFinancialProductAward(ClientNode* Client); //?
void RequestReportCommonEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //24028
void RequestGetActivityCenterInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24029
void ResponseGetActivityCenterInfo(ClientNode* Client); //24029
void RequestOpenActivityBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpenActivityBox(ClientNode* Client); //24030
void NotifyActivityCenterInfo(ClientNode* Client); //24031
void RequestGetPrivilegeIntroInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16055
void ResponseGetPrivilegeIntroInfo(ClientNode* Client); //16055
void RequestReceiveFirstReachLevelAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //16056
void ResponseReceiveFirstReachLevelAward(ClientNode* Client); //16056
void RequestGetExclusiveSpeedWayInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16060
void ResponseGetExclusiveSpeedWayInfo(ClientNode* Client); //16060
void RequestFreeSearchTreasure(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFreeSearchTresure(ClientNode* Client); //16057
void RequestFastSearchTreasureInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16058
void ResponseFastSearchTreasureInfo(ClientNode* Client); //16058
void RequestStartFastSearchTreasure(ClientNode* Client, BYTE* Body, size_t BodyLen); //16059
void ResponseStartFastSearchTreasure(ClientNode* Client); //16059
void RequestBuyConsumeVipPrivilegeItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyConsumsVipPrivilegeItem(ClientNode* Client); //16061
void NotifyClientUpdateConsumeVipRealteInfo(ClientNode* Client); //16062
void RequestGetFreeSearchTreasureAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFreeSearchTreasureAward(ClientNode* Client); //16063
void NotifyPresentItemInfo(ClientNode* Client); //24033
void RequestPresentItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //24034
void ResponsePresentItem(ClientNode* Client); //24034
void RequestGSvrdFullServiceBugletInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyFullServiceBugletInfo(ClientNode* Client); //?
void RequestWakeKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16066
void ResponseWakeKartInfo(ClientNode* Client); //16066
void RequestGetSpecifiedWakeKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16067
void ResponseGetSpecifiedWakeKartInfo(ClientNode* Client); //16067
void RequestGetAllWakeKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16068
void ResponseGetAllWakeKartInfo(ClientNode* Client); //16068
void RequestKartPartCritInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16069
void ResponseKartPartCritInfo(ClientNode* Client); //16069
void RequestExchangeWakedKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //16070
void ResponseExchangeWakedKartInfo(ClientNode* Client); //16070
void NotifyPlayerLimitedWakeKartInfo(ClientNode* Client); //16072
void NotifyPlayerRaceCardAddInfo(ClientNode* Client); //16077
void NotifyPlayerEquippedWakedKartAddAttributeValueInfo(ClientNode* Client); //16074
void NotifyDBPlayerKartWakeInfo(ClientNode* Client); //?
void RequestDBUpdatePlayerKartWakeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestDBDeletePlayerKartWakeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyRaceCardChangeInfoInRoom(ClientNode* Client); //16075
void RequestWorldEscapeInviteList(ClientNode* Client, BYTE* Body, size_t BodyLen); //24046
void ResponseWorldEscapeInviteList(ClientNode* Client); //24046
void RequestGetDropInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24043
void ResponseGetDropInfo(ClientNode* Client); //24043
void RequestGetDropList(ClientNode* Client, BYTE* Body, size_t BodyLen); //24045
void ResponseGetDropList(ClientNode* Client); //24045
void RequestBatchDeleteItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBatchDeleteItem(ClientNode* Client); //21035
void RequestDoWareHouseOperationBatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWareHouseOperationBatch(ClientNode* Client); //21036
void RequestTestMsgRTT(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTestMsgRTT(ClientNode* Client); //?
void RequestC2GGetPlayerStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //24053
void ResponseC2GGetPlayerStatus(ClientNode* Client); //24053
void RequestC2GModifyFriendRemarkName(ClientNode* Client, BYTE* Body, size_t BodyLen); //24051
void ResponseC2GModifyFriendRemarkName(ClientNode* Client); //24051
void NotifyG2CFriendRemarkName(ClientNode* Client); //24052
void RequestG2DOpFriendRemarkName(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseG2DOpFriendRemarkName(ClientNode* Client); //?
void RequestC2GFriendRemarkName(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestStoreGameMode(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStoreGameMode(ClientNode* Client); //24056
void NotifyStoredGameMode(ClientNode* Client); //24071
void NotifyGangsterCfg(ClientNode* Client); //653
void RequestUseGangsterSkillBegin(ClientNode* Client, BYTE* Body, size_t BodyLen); //657
void ResponseUseGangsterSkillBegin(ClientNode* Client); //657
void NotifyUseGangsterSkillBegin(ClientNode* Client); //658
void NotifyUseGangsterSkillOver(ClientNode* Client); //669
void RequestUseGangsterSkillOver(ClientNode* Client, BYTE* Body, size_t BodyLen); //655
void RequestGangsterSkillEffectResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //659
void NotifyGangsterSkillEffectResult(ClientNode* Client); //660
void RequestReportGangsterEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //661
void RequestGangsterPKBegin(ClientNode* Client, BYTE* Body, size_t BodyLen); //662
void ResponseGangsterPKBegin(ClientNode* Client); //662
void NotifyGangsterPKBegin(ClientNode* Client); //663
void NotifyGangsterPKOver(ClientNode* Client); //664
void RequestGangsterPKResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //665
void ResponseGangsterPKResult(ClientNode* Client); //665
void NotifyGangsterPKResult(ClientNode* Client); //666
void NotifyGangsterPlayerBlood(ClientNode* Client); //667
void NotifyGangsterPlayerScore(ClientNode* Client); //668
void NotifyGangsterPlayerEnergy(ClientNode* Client); //654
void RequestGangsterRiskCompensationBegin(ClientNode* Client, BYTE* Body, size_t BodyLen); //670
void ResponseGangsterRiskCompensationBegin(ClientNode* Client); //670
void RequestGangsterInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //673
void ResponseGangsterInfo(ClientNode* Client); //673
void RequestGangsterExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //674
void ResponseGangsterExchange(ClientNode* Client); //674
void RequestGangsterRiskCompensationOver(ClientNode* Client, BYTE* Body, size_t BodyLen); //671
void ResponseGangsterRiskCompensationOver(ClientNode* Client); //671
void NotifyGangsterMatchShow(ClientNode* Client); //672
void NotifyGansterScoreInfo(ClientNode* Client); //675
void NotifyNPCEliminateInfo(ClientNode* Client); //677
void RequestGMDGetRedEnvelopeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGMDGetRedEnvelopeInfo(ClientNode* Client); //?
void NotifyDBUpdateRedEnvelopeInfo(ClientNode* Client); //?
void NotifyRedEnvelopeInfo(ClientNode* Client); //24061
void RequestGetRedEnvelopeFriendInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRedEnvelopeFriendInfo(ClientNode* Client); //24062
void RequestGMGatherGetFriendSimpleInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGMGatherGetFriendSimpleInfo(ClientNode* Client); //?
void RequestGatherMPIDBGetFriendSimpleInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGatherMPIDBGetFriendSimpleInfo(ClientNode* Client); //?
void RequestCMSSendRedEnvelope(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCMSSendRedEnvelope(ClientNode* Client); //24063
void RequestGMGSendEnvelope(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGMGSendEnvelope(ClientNode* Client); //?
void RequestOpenRedEnvelope(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpenRedEnvelope(ClientNode* Client); //24065
void NotifyAddRedEnvelopeInfo(ClientNode* Client); //24066
void RequestLeyouyouGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24057
void ResponseLeyouyouGetInfo(ClientNode* Client); //24057
void RequestLeyouyouGetDailyBonus(ClientNode* Client, BYTE* Body, size_t BodyLen); //24058
void ResponseLeyouyouGetDailyBonus(ClientNode* Client); //24058
void RequestLeyouyouGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24059
void ResponseLeyouyouGetAward(ClientNode* Client); //24059
void RequestReturnGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReturnGetInfo(ClientNode* Client); //24206
void RequestRoomMiniGameGuessCarAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRoomMiniGameGuessCarAction(ClientNode* Client); //24207
void NotifyRoomMiniGameGuessCarInfo(ClientNode* Client); //24208
void RequestRoomMiniGameGuessFingerAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRoomMiniGameGuessFingerAction(ClientNode* Client); //24211
void NotifyRoomMiniGameGuessFingerInfo(ClientNode* Client); //24212
void Notify3DRoomPlayerActiveness(ClientNode* Client); //24213
void Request3DRoomReportCurrentObservePlayer(ClientNode* Client, BYTE* Body, size_t BodyLen); //24216
void Notify3DRoomIncreaseP2P(ClientNode* Client); //24217
void RequestDancePrepareStartGame(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDancePrepareStartGame(ClientNode* Client); //24220
void RequestDanceBattleAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDanceBattleAction(ClientNode* Client); //24221
void NotifyDanceBattleEvent(ClientNode* Client); //24222
void NotifyDanceDanceInfo(ClientNode* Client); //24223
void RequestDanceSongZan(ClientNode* Client, BYTE* Body, size_t BodyLen); //24224
void ResponseDanceSongZan(ClientNode* Client); //24224
void RequestZhanbuCommonInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseZhanbuCommonInfo(ClientNode* Client); //24226
void RequestZhanbuBet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseZhanbuBet(ClientNode* Client); //24228
void RequestZhanbuGetBuf(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseZhanbuGetBuf(ClientNode* Client); //24229
void NotifyZhanbuCurrentInfo(ClientNode* Client); //24227
void RequestZhanbuEnjoyFreeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseZhanbuEnjoyFreeInfo(ClientNode* Client); //24230
void NotifyTalkRoomEmojiInfo(ClientNode* Client); //24231
void RequestTalkRoomTarotAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTalkRoomTarotAction(ClientNode* Client); //24232
void NotifyTalkRoomTarotEvent(ClientNode* Client); //24233
void RequestTalkRoomSpyAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTalkRoomSpyAction(ClientNode* Client); //24234
void NotifyTalkRoomSpyEvent(ClientNode* Client); //24235
void RequestStartTimerChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartTimerChallenge(ClientNode* Client); //24236
void RequestReportTimerChallengeEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //24237
void ResponseReportTimerChallengeEvent(ClientNode* Client); //24237
void NotifyTimerChallengeEvent(ClientNode* Client); //24238
void NotifyTimerChallengeCommonInfo(ClientNode* Client); //24239
void RequestReportTimerChallenge2ndEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //24254
void ResponseReportTimerChallenge2ndEvent(ClientNode* Client); //24254
void NotifyTimerChallenge2ndEvent(ClientNode* Client); //24255
void NotifyTimerChallenge2ndCommonInfo(ClientNode* Client); //24256
void NotifyLuckyRecruitListFromDC(ClientNode* Client); //24242
void RequestSaveKeyTranslateInfoNew(ClientNode* Client, BYTE* Body, size_t BodyLen); //24214
void ResponseSaveKeyTranslateInfoNew(ClientNode* Client); //24214
void RequestGetKeyTranslateInfoNew(ClientNode* Client, BYTE* Body, size_t BodyLen); //24215
void ResponseGetKeyTranslateInfoNew(ClientNode* Client); //24215
void RequestHideAndSeekOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //24218
void ResponsetHideAndSeekOperate(ClientNode* Client); //24218
void NotifyHideAndSeekStatus(ClientNode* Client); //24219
void NotifyHideAndSeekSmallAnimalDup(ClientNode* Client); //24225
void RequestCrystalFightingOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //24244
void ResponseCrystalFightingOperate(ClientNode* Client); //24244
void NotifyHCrystalFightingStatus(ClientNode* Client); //24245
void NotifyChatGameUseSkill(ClientNode* Client); //459
void RequestHuanLingSuitChange(ClientNode* Client, BYTE* Body, size_t BodyLen); //24247
void ResponsetHuanLingSuitChange(ClientNode* Client); //24247
void RequestPRGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePRGetInfo(ClientNode* Client); //24085
void RequestPRGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePRGetAward(ClientNode* Client); //24086
void RequestSpringFlowerCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpringFlowerCommonCfg(ClientNode* Client); //?
void RequestSpringFlowerPlayerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpringFlowerPlayerInfo(ClientNode* Client); //?
void RequestSpringFlowerPlant(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpringFlowerPlant(ClientNode* Client); //?
void RequestQuickRPC(ClientNode* Client, BYTE* Body, size_t BodyLen); //24251
void ResponseQuickRPC(ClientNode* Client); //24251
void RequestC2SGetCosInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyCosInfo(ClientNode* Client); //?
void ResponseC2SGetCosInfo(ClientNode* Client); //?
void RequestG2MiscGetCosInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseG2MiscGetCosInfo(ClientNode* Client); //?
void NotifyServerRecordUploadInfo(ClientNode* Client); //2105
void NotifyServerRecordUrlInfo(ClientNode* Client); //2106
void NotifyShadowNPCInfo(ClientNode* Client); //2104
void RequestReportServerRecordEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //2107
void RequestThanksgivingGetVoteInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24198
void ResponseThanksgivingGetVoteInfo(ClientNode* Client); //24198
void RequestThanksgivingVote(ClientNode* Client, BYTE* Body, size_t BodyLen); //24300
void ResponseThanksgivingVote(ClientNode* Client); //24300
void RequestOpenJiaNianHuaDlg(ClientNode* Client, BYTE* Body, size_t BodyLen); //24075
void RequestGetJiaNianHuaTiliInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24079
void ResponseGetJiaNianHuaTiliInfo(ClientNode* Client); //24079
void ResponseOpenJiaNianHuaDlg(ClientNode* Client); //24075
void ResponseJiaNianHuaCfg(ClientNode* Client); //24076
void ResponseGetJiaNianHuaTopList(ClientNode* Client); //24077
void RequestGetJiaNianHuaAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24078
void ResponseGetJiaNianHuaAward(ClientNode* Client); //24078
void NotifyGroupBuyingrCfg(ClientNode* Client); //680
void RequestGetGroupBuyingInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //681
void ResponseGetGroupBuyingInfo(ClientNode* Client); //681
void RequestGroupBuyingReceiveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //682
void ResponseGroupBuyingReceiveAward(ClientNode* Client); //682
void RequestGetZhanxunExchangeInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24080
void ResponseGetZhanxunExchangeInfo(ClientNode* Client); //24080
void RequestZhanxunExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //24081
void ResponseZhanxunExchange(ClientNode* Client); //24081
void RequestGetMemberList(ClientNode* Client, BYTE* Body, size_t BodyLen); //24185
void ResponseGetMemberList(ClientNode* Client); //24185
void NotifyModifyGuildNotes(ClientNode* Client); //24083
void NotifyJoinGuildGuildNotes(ClientNode* Client); //24084
void RequestOperateGuildBlackList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOperateGuildBlackList(ClientNode* Client); //24184
void RequestGuildLeisureAreaBlackListInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildLeisureAreaBlackListInfo(ClientNode* Client); //24302
void NotifyPlayerOutGuildLeisureAreaInfo(ClientNode* Client); //24303
void RequestCheckCanInGuildLeisureAreaInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCheckCanInGuildLeisureAreaInfo(ClientNode* Client); //24304
void RequestOpenShopBuyLimitDlg(ClientNode* Client, BYTE* Body, size_t BodyLen); //24197
void RequestG2AWGetShopBuyLimit(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseG2AWGetShopBuyLimit(ClientNode* Client); //?
void ResponseOpenShopBuyLimitDlg(ClientNode* Client); //24197
void RequestGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24308
void ResponseGetAward(ClientNode* Client); //24308
void RequestDoActiveKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24310
void ResponseDoActiveKartInfo(ClientNode* Client); //24310
void RequestGetActivedKartInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24311
void ResponseGetActivedKartInfo(ClientNode* Client); //24311
void NotifySpeicifiedKartActivedSkillInfo(ClientNode* Client); //24312
void NotifyKartActiveCfgInfo(ClientNode* Client); //24313
void NotifyPlayerAllActiveKartInfo(ClientNode* Client); //24338
void NotifyClientHasJiaNianHuaGroupAwardNotReceived(ClientNode* Client); //24339
void RequestGetTowerChallengeCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //24316
void ResponseGetTowerChallengeCommonCfg(ClientNode* Client); //24316
void RequestGetTowerChallengePersonalInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24317
void ResponseGetTowerChallengePersonalInfo(ClientNode* Client); //24317
void RequestTowerOpenBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //24331
void ResponseTowerOpenBox(ClientNode* Client); //24331
void NotifyTowerBoxInfo(ClientNode* Client); //24332
void NotifyTowerBeWorshipedAwardNum(ClientNode* Client); //24333
void RequestGetTowerChallengeAreaInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24318
void ResponseGetTowerChallengeAreaInfo(ClientNode* Client); //24318
void RequestRegisterTowerChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //24319
void ResponseRegisterTowerChallenge(ClientNode* Client); //24319
void RequestGetTowerChallengePropInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24328
void ResponseGetTowerChallengePropInfo(ClientNode* Client); //24328
void RequestCheckStarCoins(ClientNode* Client, BYTE* Body, size_t BodyLen); //24320
void ResponseCheckStarCoins(ClientNode* Client); //24320
void RequestUseJumpLevelAddition(ClientNode* Client, BYTE* Body, size_t BodyLen); //24321
void ResponseUseJumpLevelAddition(ClientNode* Client); //24321
void RequestWorship(ClientNode* Client, BYTE* Body, size_t BodyLen); //24325
void ResponseWorship(ClientNode* Client); //24325
void NotifyLightOn(ClientNode* Client); //24326
void RequestStartTowerChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //24327
void ResponseStartTowerChallenge(ClientNode* Client); //24327
void RequestQuitTowerChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //24329
void NotifyTowerChallengeResult(ClientNode* Client); //24330
void RequestGuildPKGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildPKGetInfo(ClientNode* Client); //24087
void RequestGuildPKBindGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildPKBindGuild(ClientNode* Client); //24088
void RequestGuildPKGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildPKGetAward(ClientNode* Client); //24089
void RequestGuildPKGetGuildMemberList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildPKGetGuildMemberList(ClientNode* Client); //24090
void RequestFoolActivityGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24091
void ResponseFoolActivityGetInfo(ClientNode* Client); //24091
void RequestFoolActivityGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24092
void ResponseFoolActivityGetAward(ClientNode* Client); //24092
void RequestFoolActivityMakeBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //24093
void ResponseFoolActivityMakeBox(ClientNode* Client); //24093
void NotifyFoolActivityUseBoxAward(ClientNode* Client); //24094
void RequestCarLottoryGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCarLottoryGetInfo(ClientNode* Client); //24095
void RequestCarLottoryGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCarLottoryGetAward(ClientNode* Client); //24096
void NotifyClientCommonAward(ClientNode* Client); //24097
void RequestCarLottoryGetRecordList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCarLottoryGetRecordList(ClientNode* Client); //24098
void NotifyCommonSwitchOp(ClientNode* Client); //24344
void RequestTriggerBabyActionInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24800
void ResponseTriggerBabyActionInfo(ClientNode* Client); //24800
void NotifyLoverBabyActionInfo(ClientNode* Client); //24801
void RequestGetBabyDeleteAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBabyDeleteAwardInfo(ClientNode* Client); //24793
void NotifyClientRemainingFreeCrawlNums(ClientNode* Client); //24411
void RequestRaiseLoveBabyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24350
void ResponseRaiseLoverBabyInfo(ClientNode* Client); //24350
void RequestConfirmBeNoticedRaisedLoverBaby(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestChangeLoverBabyEquipStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //24386
void ResponseChangeLoverBabyEquipStatus(ClientNode* Client); //24386
void RequestConfirmRaiseLoveBabyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24351
void RequestGetLoveBabyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24352
void ResponseGetLoveBabyInfo(ClientNode* Client); //24352
void NotifyClientLoveBabyModChange(ClientNode* Client); //24373
void RequestQueryPlayerLoverBabyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24372
void ResponseQueryPlayerLoverBabyInfo(ClientNode* Client); //24372
void NotifyClientLoveBabyInfoWhenLogIn(ClientNode* Client); //24370
void RequestInteractWithTwoBaby(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseInteractWithTwoLoveBaby(ClientNode* Client); //24795
void NotifyClientUpdateTwoBabyInfo(ClientNode* Client); //24796
void RequestInteractWithLoveBaby(ClientNode* Client, BYTE* Body, size_t BodyLen); //24355
void ResponseInteractWithLoveBaby(ClientNode* Client); //24355
void RequestLikeLoverBaby(ClientNode* Client, BYTE* Body, size_t BodyLen); //24401
void ResponseLikeLoverBaby(ClientNode* Client); //24401
void RequestCheckLoverBabyLearningEnd(ClientNode* Client, BYTE* Body, size_t BodyLen); //24402
void ResponseCheckLoverBabyLearningEnd(ClientNode* Client); //24402
void NotifyClientLoverBabyLearningInfo(ClientNode* Client); //24403
void NotifyClientRaiseLoverBabyResult(ClientNode* Client); //24357
void NotifyClientReceiveRaiseLoveBabyInvition(ClientNode* Client); //24358
void NotifyClientInviteRaiseLoveBabyFailedInfo(ClientNode* Client); //24361
void NotifyClientUpdateLoveBabyInfo(ClientNode* Client); //24363
void RequestRaiseLoverBabyDirectlyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24360
void RequestGetLoverBabyDailyAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //24365
void ResponseGetLoverBabyDailyAward(ClientNode* Client); //24365
void NotifyLoverBabyBackGroundID(ClientNode* Client); //24376
void NotifyClientLoverBabyDailyAwardInfo(ClientNode* Client); //24371
void NotifyClientEntryInfo(ClientNode* Client); //24205
void RequestLMZan(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLMZan(ClientNode* Client); //24383
void NotifyLMLotteryScoreChange(ClientNode* Client); //24384
void RequestIfLMMatchAgain(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseIfLMMatchAgain(ClientNode* Client); //24382
void RequestLMMatchAnimationEnd(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyLMMatchAnimationEnd(ClientNode* Client); //24387
void NotifyJijiaFunctionItemCfg(ClientNode* Client); //24388
void NotifyClientUpdatePlayerID(ClientNode* Client); //24390
void RequestWeRelayCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWeRelayCommonCfg(ClientNode* Client); //24391
void RequestWeRelayPlayerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWeRelayPlayerInfo(ClientNode* Client); //24392
void NotifyWeRelayFriendTicketInfo(ClientNode* Client); //24393
void RequestWeRelayChooseCar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWeRelayChooseCar(ClientNode* Client); //24394
void NotifyWeRelayChooseCar(ClientNode* Client); //24395
void ResponseEnterRoom(ClientNode* Client); //104
void RequestGameLogicCommonReport(ClientNode* Client, BYTE* Body, size_t BodyLen); //636
void ResponseGameLogicCommonReport(ClientNode* Client); //636
void NotifyGameBegin(ClientNode* Client); //509
void NotifyStageBegin(ClientNode* Client); //787
void RequestGetRallyMatchActiveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRallyMatchActiveAward(ClientNode* Client); //24398
void RequestReceiveFreeCard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveFreeCardPara(ClientNode* Client); //?
void RequestSendFreeCard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSendFreeCard(ClientNode* Client); //24400
void NotifySelfRallyMatchRankChangeNum(ClientNode* Client); //24404
void NotifySendFreeCard(ClientNode* Client); //24405
void RequestSkatePropRoomZan(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSkatePropRoomZan(ClientNode* Client); //24412
void NotifySkatePropRoomZanInfo(ClientNode* Client); //24413
void NotifySkatePropRoomZanStatus(ClientNode* Client); //24414
void NotifySkatePropCoinChangeInfo(ClientNode* Client); //24415
void NotifyScoreBoxCfg(ClientNode* Client); //24423
void RequestScoreBoxStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseScoreBoxStatus(ClientNode* Client); //24424
void RequestGetScoreBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetScoreBoxAward(ClientNode* Client); //24425
void RequestGetNewHandCritBoxAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNewHandCritBoxAwardCfg(ClientNode* Client); //313
void NotifyItemType2ndCfg(ClientNode* Client); //314
void NotifyClientMatchGroupInfo(ClientNode* Client); //690
void RequestGetChatTopList(ClientNode* Client, BYTE* Body, size_t BodyLen); //386
void ResponseGetChatTopList(ClientNode* Client); //386
void RequestGetChatAreaWinnerList(ClientNode* Client, BYTE* Body, size_t BodyLen); //387
void ResponseGetChatAreaWinnerList(ClientNode* Client); //387
void RequestBeginSailTreasure(ClientNode* Client, BYTE* Body, size_t BodyLen); //389
void ResponseBeginSailTreasure(ClientNode* Client); //389
void NotifySailTreasureBegin(ClientNode* Client); //390
void RequestGetSailTreasureBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //391
void ResponseGetSailTreasureBox(ClientNode* Client); //391
void NotifySailTreasureOver(ClientNode* Client); //392
void RequestOverSailTreasure(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOverSailTreasure(ClientNode* Client); //395
void RequestSailTreasureReceiveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSailTreasureReceiveAward(ClientNode* Client); //393
void RequestSailTreasureWorship(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSailTreasureWorship(ClientNode* Client); //394
void RequestGetAwardGenerateAwardList(ClientNode* Client, BYTE* Body, size_t BodyLen); //397
void ResponseGetAwardGenerateAwardList(ClientNode* Client); //397
void NotifySailTreasureCfg(ClientNode* Client); //388
void NotifyMultiUseItemListCfg(ClientNode* Client); //347
void RequestGuildUpGetEntryInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetEntryInfo(ClientNode* Client); //24430
void RequestGuildUpGetHongbaoInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetHongbaoInfo(ClientNode* Client); //24431
void RequestGuildUpFaHongbao(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpFaHongbao(ClientNode* Client); //24432
void RequestGuildUpShouHongbao(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpShouHongbao(ClientNode* Client); //24433
void RequestGuildUpHongbaoSwitchTab(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpHongbaoSwitchTab(ClientNode* Client); //24437
void RequestGuildUpGetAvailableHongbaoInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetAvailableHongbaoInfo(ClientNode* Client); //24440
void NotifySMCGuildUpHongbaoStatus(ClientNode* Client); //24439
void RequestGuildUpGetHongbaoDetail(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetHongbaoDetail(ClientNode* Client); //24442
void RequestGuildUpGetHongbaoDailyRecord(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetHongbaoDailyRecord(ClientNode* Client); //24444
void RequestGuildUpGetHongbaoCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetHongbaoCommonCfg(ClientNode* Client); //24445
void RequestGuildUpGetHongbaoFlow(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildUpGetHongbaoFlow(ClientNode* Client); //24434
void NotifyGuildUpHongbaoMessage(ClientNode* Client); //24441
void RequestGetGuildUpWelfareBoardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildUpWelfareBoardInfo(ClientNode* Client); //24449
void RequestGetGuildUpProsperTaskAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildUpProsperTaskAward(ClientNode* Client); //24450
void NotifyActivityRecommendCfg(ClientNode* Client); //24448
void RequestReportActivityRecommendCurrentVisitInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestActivityRecommendGetGiftAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseActivityRecommendGetGiftAward(ClientNode* Client); //24447
void RequestGetGuildSpecialShop(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildSpecialShop(ClientNode* Client); //24451
void RequestGuildShopKanJia(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGuildShopKanJia(ClientNode* Client); //24452
void RequestEmbattle(ClientNode* Client, BYTE* Body, size_t BodyLen); //21120
void ResponseEmbattle(ClientNode* Client); //21120
void RequestPKAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePKAction(ClientNode* Client); //?
void NotifyPKAction(ClientNode* Client); //21122
void NotifyPKRound(ClientNode* Client); //21136
void RequestPKGameEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //21135
void ResponsePKGameEvent(ClientNode* Client); //21135
void RequestPKCaptainQTE(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePKCaptainQTE(ClientNode* Client); //?
void RequestStartPetPK(ClientNode* Client, BYTE* Body, size_t BodyLen); //21129
void ResponseStartPetPK(ClientNode* Client); //21129
void NotifyPKGameBegin(ClientNode* Client); //21124
void RequestPKPrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen); //21125
void NotifyPKWaitUnreadyLoad(ClientNode* Client); //21130
void NotifyPKBegin(ClientNode* Client); //21126
void NotifyPKOver(ClientNode* Client); //21127
void NotifyPKGameOver(ClientNode* Client); //21128
void RequestGetPKPetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPKPetInfo(ClientNode* Client); //21133
void NotifyGetPKPetMoreInfo(ClientNode* Client); //21148
void NotifyAddPet(ClientNode* Client); //586
void RequestImprovePKPet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseImprovePKPet(ClientNode* Client); //21134
void RequestGetPKPetCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //21140
void ResponseGetPKPetCfg(ClientNode* Client); //21140
void NotifyGetPKPetMoreCfg(ClientNode* Client); //21149
void RequestPKChallengeMonster(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestMonsterChallengeHistoryInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMonsterChallengeHistoryInfo(ClientNode* Client); //21138
void NotifyClientChallengeMonsterResultInfo(ClientNode* Client); //21139
void RequestPetTrialInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePetTrialInfo(ClientNode* Client); //21150
void RequestGetChatRoomPetPKInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetChatRoomPetPKInfo(ClientNode* Client); //21143
void RequestGetPetPKRankedMatchInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPetPKRankedMatchInfo(ClientNode* Client); //21144
void RequestPetPKWorship(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePetPKWorship(ClientNode* Client); //21145
void NotifyPetPKBeWorshipedAward(ClientNode* Client); //21146
void RequestGetFightPowerByStar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFightPowerByStar(ClientNode* Client); //21147
void NotifyClientCommonServerError(ClientNode* Client); //24454
void RequestDoActionInChatsvrd(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoActionInChatsvrd(ClientNode* Client); //?
void RequestReceiveGolumBallBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceiveGolumBallBoxAward(ClientNode* Client); //24455
void NotifyClientGolumBallAwardInfo(ClientNode* Client); //24456
void RequestGetGuildMemberExtendInfoInt(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildMemberExtendInfoInt(ClientNode* Client); //24457
void RequestTriggerAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyUpdateKartPhysparam(ClientNode* Client); //?
void NotifyKuangBaoAddEnergy(ClientNode* Client); //24458
void RequestKuangBaoEnter(ClientNode* Client, BYTE* Body, size_t BodyLen); //24459
void ResponseKuangBaoEnter(ClientNode* Client); //24459
void NotifyKuangBaoEnd(ClientNode* Client); //24460
void RequestKuangBaoReleaseSuperN2O(ClientNode* Client, BYTE* Body, size_t BodyLen); //24461
void ResponseKuangBaoReleaseSuperN2O(ClientNode* Client); //24461
void RequestGameModeMapCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGameModeMapCfg(ClientNode* Client); //?
void RequestPreGetCommonBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePreGetCommonBoxAward(ClientNode* Client); //24465
void NotifyPreGetCommonBoxAwardMore(ClientNode* Client); //25206
void RequestGetCommonBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestBatchGetCommonBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBatchGetCommonBoxAward(ClientNode* Client); //28321
void ResponseGetCommonBoxAward(ClientNode* Client); //24466
void RequestOpenPetPKJingJiDlg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpenPetPKJingJiDlg(ClientNode* Client); //24464
void RequestGetMagicHouseInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMagicHouseInfo(ClientNode* Client); //24470
void RequestMagicHouseCallOn(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMagicHouseCallOn(ClientNode* Client); //24471
void NotifyKartTransformersList(ClientNode* Client); //28330
void RequestGetKartTransformersInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetKartTransformersInfo(ClientNode* Client); //28331
void RequestKartTransAddPower(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseKartTransAddPower(ClientNode* Client); //28332
void NotifyOlympicOpenCfg(ClientNode* Client); //325
void RequestGetOlympicClientCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetOlympicClientCfg(ClientNode* Client); //?
void RequestOlympicReceiveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOlympicReceiveAward(ClientNode* Client); //?
void NotifyOlympicGameMedalDrop(ClientNode* Client); //?
void RequestOlympicSignUp(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOlympicSignUp(ClientNode* Client); //?
void RequestOlympicInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOlympicInfo(ClientNode* Client); //?
void RequestDonateFlame(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDonateFlame(ClientNode* Client); //?
void NotifyReportClientInfo(ClientNode* Client); //24472
void RequestReportClientInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReportClientInfo(ClientNode* Client); //?
void RequestGiveElKToSantaClaus(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGiveElkToSantaClaus(ClientNode* Client); //?
void RequestGetChritmasDayShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetChritmasDayShowInfo(ClientNode* Client); //?
void RequestStartSpecialAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartSpecialAction(ClientNode* Client); //24480
void RequestReceSpecialActionAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceSpecialActionAward(ClientNode* Client); //24481
void NotifyClientSpecialActionTreasureBoxInfo(ClientNode* Client); //24482
void RequestGetSpecialActionShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSpecialActionShowInfo(ClientNode* Client); //24483
void RequestReceChristmasDailyAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceChristmatDailyAward(ClientNode* Client); //?
void RequestGrabChristmasCouponAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGrabChristmasCouponAward(ClientNode* Client); //?
void RequestGetPurplePrivilageCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPurplePrivilageCfg(ClientNode* Client); //24491
void RequestGetPurpleMagicBallAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPurpleMagicBallAward(ClientNode* Client); //24492
void RequestGetPurpleExchangeAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPurpleExchangeAward(ClientNode* Client); //24493
void RequestPointChallengeGetGeneralCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeGetGeneralCfg(ClientNode* Client); //24496
void RequestPointChallengeGetUnlockGeneral(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeGetUnlockGeneral(ClientNode* Client); //24498
void RequestPointChallengeChangeGeneral(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeChangeGeneral(ClientNode* Client); //24497
void RequestPointChallengeUseGeneral(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeUseGeneral(ClientNode* Client); //24499
void RequestGetThemeHouseShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetThemeHouseShowInfo(ClientNode* Client); //24501
void NotifyClientMoreThemeHouseShowInfo(ClientNode* Client); //24503
void RequestReceThemeItemInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceThemeItemInfo(ClientNode* Client); //24500
void NotifyClientCollectDressUpValue(ClientNode* Client); //24502
void RequestGetMagicLampCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMagicLampCfg(ClientNode* Client); //24507
void RequestMagicLampLightOn(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMagicLampLightOn(ClientNode* Client); //24508
void NotifyGloryReturnCfg(ClientNode* Client); //?
void RequestGetGloryReturnAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGloryReturnAward(ClientNode* Client); //?
void RequestGetGloryReturnCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGloryReturnCfg(ClientNode* Client); //?
void RequestNationalCarnivalShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseNationalCarnivalShowInfo(ClientNode* Client); //?
void RequestReceNationalCarnivalAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceNationalCarnivalAward(ClientNode* Client); //?
void RequestSignUpNationalCarnivalAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSignUpNationalCarnivalAward(ClientNode* Client); //?
void NotifyClientNoviceGuideCfg(ClientNode* Client); //24506
void RequestGetNoviceGuideAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNoviceGuideAward(ClientNode* Client); //24517
void NotifyClientLoginAwardCfg(ClientNode* Client); //24518
void RequestNoviceGuideLoginAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseNoviceGuideLoginAwardCfg(ClientNode* Client); //24522
void RequestGetNoviceGuideCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNoviceGuideCfg(ClientNode* Client); //24519
void RequestVideoDisplay(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestStartNoviceGuideTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestLeaveObserve(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLeaveObserve(ClientNode* Client); //24525
void RequestLuckMatchShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLuckMatchShowInfo(ClientNode* Client); //24609
void RequestReceLuckMatchDailyRankListAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceLuckMatchDailyRankListAward(ClientNode* Client); //24605
void RequestGetLuckMatchTraningMapInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLuckMatchTrainingMapInfo(ClientNode* Client); //24600
void RequestLikeLuckMatchPlayerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLikeLuckMatchPlayerInfo(ClientNode* Client); //24601
void NotifyClientLuckMatchBeLikedPlayerInfo(ClientNode* Client); //24602
void NotifyClientUpdateLuckMatchBeLikedInfo(ClientNode* Client); //24620
void NotifyClientLikePlayerCritInfo(ClientNode* Client); //24621
void NotifyClientLuckMatchBetInfo(ClientNode* Client); //24607
void RequestLuckMatchBet(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLuckMatchBet(ClientNode* Client); //24608
void RequestLuckMatchBetAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLuckMatchBetAwardInfo(ClientNode* Client); //24610
void RequestGetLuckyMatchBetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLuckyMatchBetAward(ClientNode* Client); //24615
void RequestLuckyShopAwardCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLuckyShopAwardCfg(ClientNode* Client); //24603
void RequestLuckyShopExchangeItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLuckyShopExchangeItem(ClientNode* Client); //24604
void NotifyAnnualFestivalCfg(ClientNode* Client); //?
void RequestAnnualFestivalCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAnnualFestivalCfg(ClientNode* Client); //?
void RequestGetAnnualFestivalAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetAnnualFestivalAward(ClientNode* Client); //?
void NotifyAnnualFestivalActiveAward(ClientNode* Client); //24614
void RequestAnnualFestivalActivity(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetSpeedBuff(ClientNode* Client, BYTE* Body, size_t BodyLen); //24623
void ResponseGetSpeedBuff(ClientNode* Client); //24623
void NotifySpeedBuff(ClientNode* Client); //24624
void NotifyCrazyTimeOpen(ClientNode* Client); //24627
void RequestStealPigAssist(ClientNode* Client, BYTE* Body, size_t BodyLen); //24629
void ResponseStealPigAssist(ClientNode* Client); //24629
void RequestStealPigOpenTime(ClientNode* Client, BYTE* Body, size_t BodyLen); //24630
void ResponseStealPigOpenTime(ClientNode* Client); //24630
void NotifyStealPigActiveBoxInfo(ClientNode* Client); //24632
void RequestGetStealPigActiveAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetStealPigActiveAward(ClientNode* Client); //24633
void NotifyPlayerInvadedInfo(ClientNode* Client); //24634
void NotifyPlayerStealPigPKInfo(ClientNode* Client); //24635
void NotifyPlayerUseHammerInfo(ClientNode* Client); //24641
void NotifyPlayerAreaInfo(ClientNode* Client); //?
void RequestFindGuildByKeyName(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFindGuildByKeyName(ClientNode* Client); //24637
void NotifyAllAreaNameCfg(ClientNode* Client); //24639
void RequestPlayerAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //24640
void ResponsePlayerAction(ClientNode* Client); //24640
void RequestGetFoodFightingShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFoodFightingShowInfo(ClientNode* Client); //?
void RequestTasteFoodInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTasteFoodInfo(ClientNode* Client); //?
void RequestBlessLuckInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBlessLuckInfo(ClientNode* Client); //?
void RequestGetMagicCubesInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMagicCubesInfo(ClientNode* Client); //24642
void RequestGetGuildChampionshipInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildChampionshipInfo(ClientNode* Client); //21201
void RequestApplyGuildChampionship(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseApplyGuildChampionship(ClientNode* Client); //21202
void NotifyKeyValueInfo(ClientNode* Client); //21204
void RequestModifyGuildChampionship(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseModifyGuildChampionship(ClientNode* Client); //21203
void RequestGetGuildChampionshipRecommendGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildChampionshipRecommendGuildInfo(ClientNode* Client); //21205
void RequestFindGuildChampionshipGuild(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFindGuildChampionshipGuild(ClientNode* Client); //21206
void RequestGetGuildChampionshipBeInviteGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildChampionshipBeInviteGuildInfo(ClientNode* Client); //21207
void RequestGetGuildChampionshipGuildInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuildChampionshipGuildInfo(ClientNode* Client); //21208
void RequestMREnterChatRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //21211
void ResponseMREnterChatRoom(ClientNode* Client); //21211
void NotifyMultiRaceInfo(ClientNode* Client); //21212
void NotifyMROpponentInfo(ClientNode* Client); //21213
void NotifyMRRaceOver(ClientNode* Client); //21214
void RequestMRGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMRGetAward(ClientNode* Client); //21215
void RequestPlantMagicTree(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePlantMagicTree(ClientNode* Client); //?
void RequestDevoteRainDrop(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDevoteRainDrop(ClientNode* Client); //?
void RequestChooseFruit(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChooseFruit(ClientNode* Client); //?
void RequestRecePlantTreeAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRecePlantTreeAward(ClientNode* Client); //?
void RequestPickFruit(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePickFruit(ClientNode* Client); //?
void RequestGetMagicTreeShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMagicTreeShowInfo(ClientNode* Client); //?
void NotifyGetKubi(ClientNode* Client); //24645
void RequestReportCurMoveInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24706
void RequestGetMayDayTreasureCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMayDayTreasureCfg(ClientNode* Client); //?
void NotifyMayDayMedalAward(ClientNode* Client); //?
void RequestGetPingTuAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPingTuAward(ClientNode* Client); //?
void RequestGetMayDayWishAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMayDayWishAward(ClientNode* Client); //?
void RequestPVPLogin(ClientNode* Client, BYTE* Body, size_t BodyLen); //697
void ResponsePVPLogin(ClientNode* Client); //697
void RequestPVPLogout(ClientNode* Client, BYTE* Body, size_t BodyLen); //700
void ResponsePVPLogout(ClientNode* Client); //700
void NotifyPVPKickoff(ClientNode* Client); //702
void RequestPVPHello(ClientNode* Client, BYTE* Body, size_t BodyLen); //703
void ResponsePVPHello(ClientNode* Client); //703
void RequestC2GAlterWonderLandName(ClientNode* Client, BYTE* Body, size_t BodyLen); //24717
void ResponseC2GAlterWonderLandName(ClientNode* Client); //24717
void RequestSSCOpenStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSSCOpenStatus(ClientNode* Client); //24721
void RequestSendPwdRedEnvelope(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSendPwdRedEnvelope(ClientNode* Client); //24723
void RequestGetPwdRedEnvelopeContent(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPwdRedEnvelopeContent(ClientNode* Client); //24724
void RequestOpenMayDaySubBoard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetMagicCupCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMagicCupCfg(ClientNode* Client); //24726
void RequestGetTempBoxItemInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetTempBoxItemInfo(ClientNode* Client); //24727
void RequestMagicCupGetAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMagicCupGetAward(ClientNode* Client); //24728
void RequestMagicCupExchangePiece(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMagicCupExchangePiece(ClientNode* Client); //24729
void NotifyCommonRaceAward(ClientNode* Client); //24730
void RequestGetZongXiangShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetZongXiangShowInfo(ClientNode* Client); //?
void RequestMakeZongzi(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMakeZongzi(ClientNode* Client); //?
void RequestZongziAnswerQuestion(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestSaishiAnswerQuestion(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSaishiAnswerQuestion(ClientNode* Client); //24736
void ResponseZongziAnswerQuestion(ClientNode* Client); //24733
void RequestGetZongziQuestionInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetSaishiQuestionInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetZongziQuestionInfo(ClientNode* Client); //?
void ResponseGetSaishiQuestionInfo(ClientNode* Client); //24735
void RequestGetGoldMedalMatchInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGoldMedalMatchInfo(ClientNode* Client); //21226
void RequestApplyGoldMedalMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseApplyGoldMedalMatch(ClientNode* Client); //21227
void RequestBuyScoreGoldMedalMatch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBuyScoreGoldMedalMatch(ClientNode* Client); //21228
void RequestGetItemTimeLimtCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //24201
void ResponsetGetItemTimeLimtCfg(ClientNode* Client); //24201
void RequestHyperSpaceJumboGetCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseHyperSpaceJumboGetCfg(ClientNode* Client); //24202
void RequestTimerChallenge2ndMoreHallInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTimerChallenge2ndMoreHallInfo(ClientNode* Client); //24258
void RequestGetGuanjiaInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGuanjiaInfo(ClientNode* Client); //24259
void RequestZan(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseZan(ClientNode* Client); //24260
void NotifyOpenFireCracker(ClientNode* Client); //28384
void NotifyZan(ClientNode* Client); //24261
void RequestGetChattingBlackUinList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetChattingBlackUinList(ClientNode* Client); //24265
void RequestChangeChattingBlackUin(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChangeChattingBlackUin(ClientNode* Client); //24266
void RequestHyperSpaceJumboOperation(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseHyperSpaceJumboSelectOperation(ClientNode* Client); //24204
void RequestRptSpeedFastClickInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestSpeedFastShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpeedFastShowInfo(ClientNode* Client); //?
void RequestMoveTurnTableInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMoveTurnTableInfo(ClientNode* Client); //?
void RequestPointChallengeBuyItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeBuyItem(ClientNode* Client); //24753
void RequestPointChallengeOpenMainBoard(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePointChallengeOpenMainBoard(ClientNode* Client); //24754
void NotifyGenGameEndBoxAward(ClientNode* Client); //24755
void RequestGetGameEndBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetZhangFeiBoxList(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetZhangFeiBoxList(ClientNode* Client); //24766
void NotifySpecialActivityInfo(ClientNode* Client); //24767
void RequestOpenGlobalTravel(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseOpenGlobalTravel(ClientNode* Client); //24768
void RequestGlobalTravelRefreshItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGlobalTravelRefreshItem(ClientNode* Client); //24769
void NotifyQiXiZhanBuCfg(ClientNode* Client); //24778
void RequestGetValentinesDayCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetValentinesDayCfg(ClientNode* Client); //?
void RequestTieRedRop(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTieRedRop(ClientNode* Client); //?
void RequestInviteToBeSNSPerson(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseInviteToBeSNSPerson(ClientNode* Client); //?
void NotifyInvitedToBeSNSPerson(ClientNode* Client); //24773
void RequestCancelToBeSNSPerson(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCancelToBeSNSPerson(ClientNode* Client); //?
void NotifyCancelToBeSNSPerson(ClientNode* Client); //?
void RequestSendGiftToSNSPerson(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSendGiftToSNSPerson(ClientNode* Client); //?
void NotifyReceiveGiftFromSNSPerson(ClientNode* Client); //?
void RequestGetSNSPersonMixInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSNSPersonMixInfo(ClientNode* Client); //?
void RequestGetSNSGift(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSNSGift(ClientNode* Client); //?
void RequestGetLBFairgroundInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLBFairgroundInfo(ClientNode* Client); //24781
void RequestLBFairgroundPlay(ClientNode* Client, BYTE* Body, size_t BodyLen); //24782
void ResponseLBFairgroundPlay(ClientNode* Client); //24782
void NotifyLBFairgroundInfo(ClientNode* Client); //24783
void RequestGetLoveCrystalInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetLoveCrystalInfo(ClientNode* Client); //24784
void RequestAddLoveCrystalValue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseAddLoveCrystalValue(ClientNode* Client); //24785
void RequestGetQiXiZhanBuCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetQiXiZhanBuCfg(ClientNode* Client); //24797
void RequestGetArrestGameCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetArrestGameCfg(ClientNode* Client); //24805
void RequestArrestReportRank(ClientNode* Client, BYTE* Body, size_t BodyLen); //24806
void RequestArrestQuitStatus(ClientNode* Client, BYTE* Body, size_t BodyLen); //24809
void NotifyPlayerRaceOver(ClientNode* Client); //24810
void RequestTwistMachineShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTwistMachineShowInfo(ClientNode* Client); //?
void RequestTwistMachineInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTwistMachineInfo(ClientNode* Client); //?
void NotifyWareHousePermanentItemList(ClientNode* Client); //693
void NotifyAllCityGameLogicInfo(ClientNode* Client); //24807
void RequestAllCityReportEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //24808
void ResponseAllCityReportEvent(ClientNode* Client); //24808
void NotifyAllCityCfg(ClientNode* Client); //24811
void RequestReportAllCityDetailInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //24812
void ResponseReportAllCityDetailInfo(ClientNode* Client); //24812
void RequestGetExchangeShopInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetExchangeShopInfo(ClientNode* Client); //24786
void RequestDoShopExchange(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoShopExchange(ClientNode* Client); //24787
void NotifyClientUpdateItemDescInfo(ClientNode* Client); //24379
void RequestGetThanksGivingCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetThanksGivingCfg(ClientNode* Client); //?
void RequestGetThanksGivingWishAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetThanksGivingWishAward(ClientNode* Client); //?
void RequestGetThanksGivingFinalAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetThanksGivingFinalAward(ClientNode* Client); //?
void NotifyHelperInfo(ClientNode* Client); //24820
void RequestThanksGivingOpenBox(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseThanksGivingOpenBox(ClientNode* Client); //?
void NotifyTVLiveInfo(ClientNode* Client); //24822
void RequestGetRankedMatchShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRankedMatchShowInfo(ClientNode* Client); //25000
void RequestGetRankedMatchMapRecordInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRankedMatchMapRecordInfo(ClientNode* Client); //25014
void RequestGetRankedMatchSeasonRptInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRankedMatchSeasonRptInfo(ClientNode* Client); //25015
void NotifyRankedMatchSeasonInfo(ClientNode* Client); //25005
void NotifyRankedMatchPromotionAwardInfo(ClientNode* Client); //25003
void RequestRankedMatchPersonalPanelInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRankedMatchPersonalPanelInfo(ClientNode* Client); //25012
void RequestRankedMatchPannelOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRankedMatchPannelOperate(ClientNode* Client); //25013
void NotifyErrorInfo(ClientNode* Client); //720
void RequestTenYearsActivityShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTenYearsActivityShowInfo(ClientNode* Client); //?
void RequestTenYearsBless(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTenYearsBless(ClientNode* Client); //?
void RequestEquipSeal(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseEquipSeal(ClientNode* Client); //25063
void NotifyTenYearsCfgInfo(ClientNode* Client); //?
void RequestC2SSaveDIYMapFile(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseC2SSaveDIYMapFile(ClientNode* Client); //1716
void NotifyG2CSaveDIYMapFileResult(ClientNode* Client); //1717
void NotifyTenYearsCapusleInfo(ClientNode* Client); //?
void RequestSharePostCardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSharePostCardInfo(ClientNode* Client); //?
void NotifyClientDomainResolve(ClientNode* Client); //2100
void RequestReportDomainResolveResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //2101
void RequestReportGameFrameInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //2102
void RequestReportGameFrameCheckInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //2103
void RequestGetNewSpringYearsShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNewSpringYearShowInfo(ClientNode* Client); //?
void RequestExtractLuckBagInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseExtractLuckBagInfo(ClientNode* Client); //?
void RequestGetBigDeliveryShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBigDeliveryShowInfo(ClientNode* Client); //?
void RequestMakeWishForBigDelivery(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMakeWishForBigDelivery(ClientNode* Client); //?
void NotifyMakeWishAwardInfo(ClientNode* Client); //?
void NotifyTopUIItemInfo(ClientNode* Client); //25116
void RequestGetBarrageInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetBarrageInfo(ClientNode* Client); //25107
void NotifyGetBarrageMoreInfo(ClientNode* Client); //25109
void RequestSendOneBarrage(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSendOneBarrage(ClientNode* Client); //25106
void RequestReportMapDIYEditInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //25108
void ResponseReportMapDIYEditInfo(ClientNode* Client); //25108
void RequestInternationalSeriesGetInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseInternationalSeriesGetInfo(ClientNode* Client); //25110
void RequestInternationalSeriesGetChallengeData(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseInternationalSeriesGetChallengeData(ClientNode* Client); //25111
void RequestInternationalSeriesOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseInternationalSeriesOperate(ClientNode* Client); //25112
void NotifyInternationalSeriesChallengeResult(ClientNode* Client); //25113
void RequestGetDreamKiteCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetDreamKiteCfg(ClientNode* Client); //?
void RequestMakeDreamKite(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMakeDreamKite(ClientNode* Client); //?
void RequestFlyDreamKite(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFlyDreamKite(ClientNode* Client); //?
void RequestDreamKiteHelp(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDreamKiteHelp(ClientNode* Client); //?
void RequestDreamKiteBeHelpedHistory(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDreamKiteBeHelpedHistory(ClientNode* Client); //?
void NotifyDreamKiteHelpInfo(ClientNode* Client); //25123
void NotifyClientNewDay(ClientNode* Client); //25125
void RequestGetDailyExtractShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetDailyExtractShowInfo(ClientNode* Client); //25130
void RequestChooseAwardForDailyExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseChooseAwardForDailyExtract(ClientNode* Client); //25132
void RequestDailyExtractInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDailyExtractInfo(ClientNode* Client); //25131
void RequestGetMakeFoodActShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMakeFoodActShowInfo(ClientNode* Client); //24764
void RequestMakeFood(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMakeFood(ClientNode* Client); //24765
void RequestFastSearchTreasureCfgInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFastSearchTreasureCfgInfo(ClientNode* Client); //?
void RequestGetTrackTreasureShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetTrackTreasureShowInfo(ClientNode* Client); //?
void RequestStartTrackTreasureSearch(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartTrackTreasureSearch(ClientNode* Client); //?
void RequestGetQuanmingTreasureShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQuanmingTreasureShowInfo(ClientNode* Client); //?
void RequestQuanmingTreasureExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQuanmingTreasureExtract(ClientNode* Client); //?
void RequestSpecialActDevote(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpecialActDevote(ClientNode* Client); //?
void RequestGetWeekLyGiftInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWeekLyGiftInfo(ClientNode* Client); //25135
void RequestWeeklyGiftExchangeQualification(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseWeeklyGiftExchangeQualification(ClientNode* Client); //25136
void RequestGetIndianaChanllageCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetIndianaChanllageCfg(ClientNode* Client); //?
void NotifyMuchPlayerInfo(ClientNode* Client); //1718
void NotifyMuchPlayerMoreInfo(ClientNode* Client); //1719
void NotifyMuchPlayerGameBegin(ClientNode* Client); //?
void NotifyMuchPlayerKartPhysParamInfo(ClientNode* Client); //?
void NotifyMuchPlayerKartPhysParamMoreInfo(ClientNode* Client); //?
void NotifyMuchPlayerRaceOver(ClientNode* Client); //1721
void NotifyInfectionGameStatus(ClientNode* Client); //1724
void RequestInfectionAction(ClientNode* Client, BYTE* Body, size_t BodyLen); //1725
void ResponseInfectionAction(ClientNode* Client); //1725
void NotifyCrazyChaseGameEvent(ClientNode* Client); //1726
void RequestGetWorldCupShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetWorldCupShowInfo(ClientNode* Client); //?
void RequestStartShoot(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartShoot(ClientNode* Client); //?
void RequestGetMakeZongziShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMakeZongziShowInfo(ClientNode* Client); //?
void RequestRefreshAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRefreshAwardInfo(ClientNode* Client); //?
void RequestStartMakeZongzi(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartMakeZongzi(ClientNode* Client); //?
void RequestLightZongzi(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLightZongzi(ClientNode* Client); //?
void RequestGetSummerZhanxinShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSummerZhanxinShowInfo(ClientNode* Client); //?
void RequestGetPresentStarValueRecordInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPresentStarValueRecordInfo(ClientNode* Client); //?
void RequestGetPresentPlayerListInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetPresentPlayerListInfo(ClientNode* Client); //?
void RequestLightSummerStar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLightSummerStar(ClientNode* Client); //?
void RequestConstellateCallOn(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseConstellateCallOn(ClientNode* Client); //?
void RequestGetConstellateCallOnShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetConstellateCallOnShowInfo(ClientNode* Client); //?
void RequestPresentStarValue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponsePresentStarValue(ClientNode* Client); //?
void RequestReceStarValue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceStarValue(ClientNode* Client); //?
void RequestSummerZhanbu(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSummerZhanBu(ClientNode* Client); //?
void RequestGetZhanbuShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetZhanbuShowInfo(ClientNode* Client); //?
void RequestSuperSpokesPerson(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSuperSpokesPerson(ClientNode* Client); //25139
void NotifyDesperateEscapeGameEvent(ClientNode* Client); //1727
void RequestDesperateEscapeGetTrophyInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDesperateEscapeGetTrophyInfo(ClientNode* Client); //1730
void RequestDesperateEscapeEquipTrophy(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDesperateEscapeEquipTrophy(ClientNode* Client); //1731
void NotifyMatchRoomInfo(ClientNode* Client); //1728
void NotifyGameBeginForRecord(ClientNode* Client); //1735
void NotifySuperRaceInfo(ClientNode* Client); //25140
void RequestSuperRaceOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSuperRaceOperate(ClientNode* Client); //?
void RequestGetSummerActShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSummerActShowInfo(ClientNode* Client); //28220
void RequestDoSummerActExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoSummerActExtract(ClientNode* Client); //28221
void RequestMonopolyCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseMonopolyCfg(ClientNode* Client); //28225
void RequestGetMonopolyAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetMonopolyAward(ClientNode* Client); //28226
void RequestSelectAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSelectAward(ClientNode* Client); //28227
void RequestGetHappyLuckyCoinShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetHappyLuckyCoinShowInfo(ClientNode* Client); //28222
void RequestDoHappyLuckyCoinExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoHappyLuckyCoinExtract(ClientNode* Client); //28223
void RequestCarExchangeCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCarExchangeCfg(ClientNode* Client); //28230
void RequestGetCarExchangeAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetCarExchangeAward(ClientNode* Client); //28231
void RequestCarRefitInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseCarRefitInfo(ClientNode* Client); //28233
void RequestReportCarPickInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReportCarPickInfo(ClientNode* Client); //28234
void RequestGetSuperTurkeyShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSuperTurkeyShowInfo(ClientNode* Client); //28300
void RequestDoSuperTurkeyExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoSuperTurkeyExtract(ClientNode* Client); //28301
void RequestGetSuperTurkeyFriendListInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSuperTurkeyFriendListInfo(ClientNode* Client); //28302
void RequestDoSuperTurkeyHelp(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoSuperTrukeyHelp(ClientNode* Client); //28303
void RequestGetSuperTurkeyHelpedPlayerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSuperTurkeyHelpedPlayerInfo(ClientNode* Client); //28304
void RequestDoSuperTurkeyShare(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoSuperTurkeyShare(ClientNode* Client); //28305
void RequestReceSuperTurkeyShareAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseReceSuperTurkeyShareAwardInfo(ClientNode* Client); //28306
void NotifyShuangRenCheGameEvent(ClientNode* Client); //28235
void RequestShuangRenCheGetCarInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseShuangRenCheGetCarInfo(ClientNode* Client); //?
void RequestShuangRenCheEquipCar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseShuangRenCheEquipCar(ClientNode* Client); //?
void RequestChangeRole(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyChangeRole(ClientNode* Client); //28239
void RequestResponseChangeRole(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void NotifyChangeRoleResult(ClientNode* Client); //28241
void RequestRefreshMonster(ClientNode* Client, BYTE* Body, size_t BodyLen); //28242
void ResponseRefreshMonster(ClientNode* Client); //28242
void RequestShuangRenCheExtraAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseShuangRenCheExtraAward(ClientNode* Client); //28243
void RequestGetGoldenBellShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGoldenBellShowInfo(ClientNode* Client); //28307
void RequestShakeGoldBell(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseShakeGoldBell(ClientNode* Client); //28308
void RequestGetFiveDaysExchangeCarsInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetFiveDaysExchangeCarsInfo(ClientNode* Client); //28371
void RequestFiveDaysExchangeCarsRefreshAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFiveDaysExchangeCarsRefershAwardInfo(ClientNode* Client); //28373
void RequestFiveDaysExchangeCarsDrawLottory(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFiveDaysExchangeCarsDrawLottory(ClientNode* Client); //28372
void RequestGetSpecialActivityInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSpecialActivityInfo(ClientNode* Client); //28374
void RequestSpecialActivityDoLottery(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpecialActivityDoLottery(ClientNode* Client); //28375
void RequestRecePresentBoxItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRecePresentBoxItem(ClientNode* Client); //28313
void RequestFindBackAniversaryCoin(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseFindBackAniversaryCoin(ClientNode* Client); //28314
void RequestElevenAniversaryPresentShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseElevenAniversaryPresentShowInfo(ClientNode* Client); //28309
void RequestGetElevenAniversaryLuckyEggInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetElevenAniversaryLuckyEggInfo(ClientNode* Client); //28315
void RequestDoElevenAniversaryMakeWish(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoElevenAniversaryMakeWish(ClientNode* Client); //28310
void RequestElevenAniversaryPresentBoxInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseElevenAniversaryPresentBoxInfo(ClientNode* Client); //28311
void RequestRefreshSpecialAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRefershSpecialAwardInfo(ClientNode* Client); //28312
void NotifyTeamN2OProgressInc(ClientNode* Client); //1207
void NotifyClientXCarEvent(ClientNode* Client); //5100
void NotifyClientSkillTrainingTipsInfo(ClientNode* Client); //28341
void RequestReportSkillTrainingTips(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void RequestGetTrainingSkillInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetTrainingSkillInfo(ClientNode* Client); //28343
void NotifyClientSkillTrainingMapInfo(ClientNode* Client); //28344
void RequestRestartSingleTask(ClientNode* Client, BYTE* Body, size_t BodyLen); //28345
void ResponseRestartSingleTask(ClientNode* Client); //28345
void RequestGetNewSpringBlessingShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetNewSpringBlessingShowInfo(ClientNode* Client); //28360
void RequestStartDoNewSpringBlessingExtract(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDoNewSpringBlessingExtract(ClientNode* Client); //28361
void RequestGetSpringLuckyBagInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSpringLuckyBagInfo(ClientNode* Client); //28362
void RequestExchangeFuziItem(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseExchangeFuziItem(ClientNode* Client); //28363
void RequestGetGrowUpShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGrowUpShowInfo(ClientNode* Client); //16078
void RequestGrowUp(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGrowUp(ClientNode* Client); //16079
void RequestGetGrowUpLogInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetGrowUpLogInfo(ClientNode* Client); //16080
void NotifyClientHopeAction(ClientNode* Client); //24099
void RequestGetSecretCompassInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetSecretCompassInfo(ClientNode* Client); //28376
void RequestSecretCompassDrawLottery(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSecretCompassDrawLottery(ClientNode* Client); //28377
void NotifyClientCommonEvent(ClientNode* Client); //28381
void RequestSpecialActSocialInvite(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseSpecialActSocialInvite(ClientNode* Client); //?
void NotifySpecialActSocialInvite(ClientNode* Client); //?
void RequestDragonBoatRaceShowInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDragonBoatRaceShowInfo(ClientNode* Client); //?
void RequestDragonBoatRaceSelectAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDragonBoatRaceSelectAward(ClientNode* Client); //?
void RequestDragonBoatRaceStartRace(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDragonBoatRaceStartRace(ClientNode* Client); //?
void RequestDragonBoatRaceHelpPlayerInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseDragonBoatRaceHelpPlayerInfo(ClientNode* Client); //?
void RequestKartRefitAttrTransfer(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseRefitKartAttrTransfer(ClientNode* Client); //1208
void RequestGetKartRefitAttrTransferInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetRefitKartAttrTransferInfo(ClientNode* Client); //1214
void RequestReportAntiCollisionDataBuff(ClientNode* Client, BYTE* Body, size_t BodyLen); //26114
void NotifyRedPointInfo(ClientNode* Client); //25114
void RequestBPGetCoreAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseBPGetCoreAward(ClientNode* Client); //28382
void NotifyGameBuffCfg(ClientNode* Client); //28404
void NotifyQSLabTriggerAffect(ClientNode* Client); //28405
void RequestQsLabCheckTrigger(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabCheckTrigger(ClientNode* Client); //28406
void RequestGetQsLabReviewInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetQsLabReviewInfo(ClientNode* Client); //28411
void RequestGetQsLabCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetQsLabCommonCfg(ClientNode* Client); //28385
void RequestGetQsLabSeasonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //28386
void ResponseGetQsLabSeasonCfg(ClientNode* Client); //28386
void NotifyQsLabSeasonMoreInfo(ClientNode* Client); //28387
void NotifyQsLabSeasonInfo(ClientNode* Client); //28388
void RequestQsLabStartMove(ClientNode* Client, BYTE* Body, size_t BodyLen); //28389
void ResponseQsLabStartMove(ClientNode* Client); //28389
void RequestQsLabUnlockMist(ClientNode* Client, BYTE* Body, size_t BodyLen); //28407
void ResponseQsLabUnlockMist(ClientNode* Client); //28407
void RequestQsLabUsePortal(ClientNode* Client, BYTE* Body, size_t BodyLen); //28409
void ResponseQsLabUsePortal(ClientNode* Client); //28409
void RequestQsLabUseRail(ClientNode* Client, BYTE* Body, size_t BodyLen); //28410
void ResponseQsLabUseRail(ClientNode* Client); //28410
void RequestQsLabStopMove(ClientNode* Client, BYTE* Body, size_t BodyLen); //28390
void ResponseQsLabStopMove(ClientNode* Client); //28390
void NotifyQsLabMoveChange(ClientNode* Client); //28391
void RequestQsLabUseLadderSwitch(ClientNode* Client, BYTE* Body, size_t BodyLen); //28392
void ResponseQsLabUseLadderSwitch(ClientNode* Client); //28392
void RequestQsLabLightTower(ClientNode* Client, BYTE* Body, size_t BodyLen); //28393
void ResponseQsLabLightTower(ClientNode* Client); //28393
void RequestQsLabLightTowerPerformace(ClientNode* Client, BYTE* Body, size_t BodyLen); //28394
void ResponseQsLabLightTowerPerformace(ClientNode* Client); //28394
void RequestQsLabUseLaserCannon(ClientNode* Client, BYTE* Body, size_t BodyLen); //28395
void ResponseQsLabUseLaserCannon(ClientNode* Client); //28395
void RequestQsLabBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabBoxAward(ClientNode* Client); //28398
void RequestQsLabUseSprinkler(ClientNode* Client, BYTE* Body, size_t BodyLen); //28399
void ResponseQsLabUseSprinkler(ClientNode* Client); //28399
void RequestQsLabChangeCar(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabChangeCar(ClientNode* Client); //28400
void RequestQsLabGetBuffBoxInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabGetBuffBoxInfo(ClientNode* Client); //28401
void RequestQsLabChooseBuff(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabChooseBuff(ClientNode* Client); //28402
void RequestQsLabBackTime(ClientNode* Client, BYTE* Body, size_t BodyLen); //28403
void ResponseQsLabBackTime(ClientNode* Client); //28403
void RequestQsLabUseDogHouse(ClientNode* Client, BYTE* Body, size_t BodyLen); //28418
void ResponseQsLabUseDogHouse(ClientNode* Client); //28418
void RequestQsLabCommonEvent(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabCommonEvent(ClientNode* Client); //28408
void RequestQsLabCommittalTaskInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQsLabCommittalTaskInfo(ClientNode* Client); //28419
void RequestQslabChangePokeCard(ClientNode* Client, BYTE* Body, size_t BodyLen); //28426
void ResponseQslabChangePokeCard(ClientNode* Client); //28426
void RequestQslabReportClue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQslabReportClue(ClientNode* Client); //28427
void RequestQslabOpenClue(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseQslabOpenClue(ClientNode* Client); //28428
void RequestLightPointCfg(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseLightPointCfg(ClientNode* Client); //28396
void RequestStartLightPointChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseStartLightPointChallenge(ClientNode* Client); //28397
void RequestGetTaskAwardInfo(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetTaskAwardInfo(ClientNode* Client); //28380
void RequestGetQuickRaceTimeRandMap(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseGetQuickRaceTimeRandMap(ClientNode* Client); //28379
void RequestDoBagItemShowOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //28412
void ResponseDoBagItemShowOperate(ClientNode* Client); //28412
void NotifyItemObtainedOrderInfo(ClientNode* Client); //1217
void RequestDressInfoOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //28413
void ResponseDressInfoOperate(ClientNode* Client); //28413
void NotifyClientCosOpAuth(ClientNode* Client); //28414
void RequestReportCosOpResult(ClientNode* Client, BYTE* Body, size_t BodyLen); //28415
void RequestCommonReportToMatchRoom(ClientNode* Client, BYTE* Body, size_t BodyLen); //24478
void NotifyGameLogicPoint(ClientNode* Client); //28420
void RequestReplayOperate(ClientNode* Client, BYTE* Body, size_t BodyLen); //28421
void ResponseReplayOperate(ClientNode* Client); //28421
void NotifyAddPlayer(ClientNode* Client); //712
void RequestTimerChallenge3Operate(ClientNode* Client, BYTE* Body, size_t BodyLen); //?
void ResponseTimerChallenge3Operate(ClientNode* Client); //28425
void NotifyAbnormalCurrentInfo(ClientNode* Client); //28429
