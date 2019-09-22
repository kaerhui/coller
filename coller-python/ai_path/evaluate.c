/*
 * evaluate.c
 *
 *  Created on: Sep 13, 2018
 *      Author: Administrator
 */
#include "junqi.h"
#include "engine.h"
#include "path.h"


#undef log_a
#define log_a(format,...)

const u8 gChessValue[14] =
{
    0,//none
    0,//dark
    0,//junqi
    100,//dilei
    110,//zhadan
    210,//siling
    190,//junzh
    150,//shizh
    100,//lvzh
    85,//tuanzh
    50,//yingzh
    40,//lianzh
    30,//paizh
    90,//gongb
};
void InitValuePara(Value_Parameter *p)
{
//	p->vChess[SILING] = 210;
//	p->vChess[JUNZH] = 190;
//	p->vChess[SHIZH] = 150;
//	p->vChess[LVZH] = 100;
//	p->vChess[TUANZH] = 85;
//	p->vChess[YINGZH] = 50;
//	p->vChess[LIANZH] = 40;
//	p->vChess[PAIZH] = 30;
//	p->vChess[GONGB] = 90;
//	p->vChess[DILEI] = 100;
//	p->vChess[ZHADAN] = 110;
    for(int i=DILEI; i<=GONGB; i++)
    {
        p->vChess[i] = gChessValue[i];
    }
	p->vDarkLand =  20;
	p->vDarkBomb =  10;
	p->vDarkJunqi = 20;
	p->vPathLand = 10;
	p->vPathChess = 5;
	p->vDanger = 100;

	p->vAllChess = p->vChess[SILING]+
	        p->vChess[JUNZH]+
	        p->vChess[SHIZH]*2+
	        p->vChess[LVZH]*2+
	        p->vChess[TUANZH]*2+
	        p->vChess[YINGZH]*2+
	        p->vChess[LIANZH]*3+
	        p->vChess[PAIZH]*3+
	        p->vChess[GONGB]*3+
	        p->vChess[DILEI]*3+
	        p->vChess[ZHADAN]*2+
	        p->vDarkLand*8+
	        p->vDarkBomb*20+
	        p->vDarkJunqi;
	log_a("all value %d",p->vAllChess);
}

int CheckCampValue(Junqi *pJunqi, int iDir)
{
    int val = 0;
    int i;
    u8 aCamp[5] = {6,8,12,16,18};
    u16 aCampVal[5] = {40,40,70,90,90};
    BoardChess *pChess;

    for(i=0; i<5; i++)
    {
        pChess = &pJunqi->ChessPos[iDir][aCamp[i]];
        if(pChess->type==NONE)
        {
            continue;
        }
        else
        {
            if( (pChess->pLineup->iDir&1)!=(iDir&1) )
            {
                if( pChess->pLineup->type==GONGB &&
                        (iDir&1)!=ENGINE_DIR )
                {
                    continue;
                }

                if( i>2 && pJunqi->ChessPos[iDir][aCamp[i]+10].type==JUNQI)
                {
                    aCampVal[i] += 40;
                    if( (iDir&1)==ENGINE_DIR )//下营不能被敌人占掉
                    {
                        if( pJunqi->aInfo[iDir].value<2000 )
                        {
                            aCampVal[i] += 200;
                        }
                        else
                        {
                            aCampVal[i] += 20;
                        }

                    }
                    val += 10;
                    log_a("camp1 val %d ",val);
                }
                else if( i==2 && (iDir&1)==ENGINE_DIR )
                {
                    aCampVal[i] += 20;
                }

                if( pChess->isCamp!=2 )//空营没有价值
                {
                    val += aCampVal[i];
                    log_a("camp2 val %d ",val);
                }
                log_a("camp type %d i %d",pChess->isCamp,i);

                if( pJunqi->iRpOfst>100 && (iDir&1)!=ENGINE_DIR
                        && pChess->isCamp!=2 )

                {

                    int tempDir;
                    int oppsDir;
                    tempDir = pChess->pLineup->iDir;
                    if( pChess->pLineup->type==pJunqi->aInfo[tempDir].mxType  )
                    {
                        oppsDir = (tempDir+2)&3;
                        if( pJunqi->aInfo[oppsDir].bDead ||
                            pChess->pLineup->type<=pJunqi->aInfo[oppsDir].mxType )
                        {
                            val -= aCampVal[i];
                            log_a("camp3 val %d ",val);
                        }
                    }
                    else if( pChess->pLineup->type<LVZH )
                    {
                        //大字应该控盘而不是进营
                        val -= (aCampVal[i]>>1);
                        log_a("camp4 val %d ",val);
                    }
                }

            }
            else
            {
                log_a("idr %d %d isNotBomb %d",iDir,
                        pChess->pLineup->iDir,
                        pChess->pLineup->isNotBomb );
                if( pChess->pLineup->isNotBomb )
                {
                    val += 5;
                    log_a("camp5 val %d ",val);
                }
                if( pJunqi->aInfo[iDir].isEnemyInCamp )
                {
                    if( (pChess->pLineup->iDir&1)==ENGINE_DIR &&
                            22==pChess->pLineup->index )
                    {
                        val -= 30;
                    }
                }
                //本意打算让炸弹回下营防守，不知为何加了这句胜率就变得很低
//                if( pChess->isBottom && pChess->type==ZHADAN )
//                {
//                    val -= 10;
//                }
            }
        }
    }
//    if( pJunqi->iRpOfst>100 && pJunqi->nNoEat>10 )
//    {
//        log_a("no eat ignore camp ");
//        val = 0;
//    }
    log_a("camp %d %d",val,iDir);
    return val;
}

int CalDirPathValue(Junqi *pJunqi, int iDir, u8 *pDir)
{
    int i;
    int value = 0;
    BoardChess *pChess;
    Engine *pEngine;
    Value_Parameter *pVal;

    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;

    for(i=0;i<4;i++)
    {
        pChess = &pJunqi->ChessPos[iDir][pDir[i]];
        if( pChess->type!=NONE )
        {
            if((pChess->pLineup->iDir&1)==(iDir&1))
            {
                value += pVal->vPathChess;
            }
            else
            {
                value -= pVal->vPathChess;
            }
        }
    }

    return value;
}

int CalTripleValue(Junqi *pJunqi, int iDir, u8 *pDir, u8 bShowFlag)
{
    int i;
    int value = 0;
    BoardChess *pChess;
    Engine *pEngine;
    Value_Parameter *pVal;

    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;

    for(i=0;i<2;i++)
    {
        pChess = &pJunqi->ChessPos[iDir][pDir[i]];
        if( pChess->type!=NONE )
        {
            if((pChess->pLineup->iDir&1)==(iDir&1))
            {
                if( pChess->pLineup->isNotLand )
                {
                    value += pVal->vChess[TUANZH];
                }
                else
                {
                    value += pVal->vChess[SHIZH];
                }
            }
            else
            {
                value -= pVal->vChess[SILING];
            }
        }

        if(bShowFlag) break;
    }

    return value;
}

int CalCornerValue(Junqi *pJunqi, int iDir, u8 *pDir)
{
    int value = 0;
    BoardChess *pChess;
    Engine *pEngine;
    Value_Parameter *pVal;

    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;

    pChess = &pJunqi->ChessPos[iDir][pDir[0]];
    if( pChess->type!=NONE )
    {
        if((pChess->pLineup->iDir&1)==(iDir&1))
        {
            if( pChess->pLineup->isNotLand )
            {
                value += pVal->vPathChess;
            }
            else
            {
                value += pVal->vChess[LVZH];
            }
        }
        else
        {
            value -= pVal->vChess[SHIZH];
        }
    }

    return value;
}

int CalMiddleValue(Junqi *pJunqi, int iDir, u8 *pDir)
{
    int value = 0;

    value += CalCornerValue(pJunqi,iDir,pDir)>>1;
    value += CalTripleValue(pJunqi,iDir,&pDir[1],1)>>1;

    return value;
}

int CalDangerValue(Junqi *pJunqi, int iDir, u8 *pDir)
{
    int value = 0;
    BoardChess *pChess;

    int i;
    int landFlag1 = 0;
    int landFlag2 = 0;
    int landFlag3 = 0;
    int vDanger;
    Engine *pEngine;
    Value_Parameter *pVal;

    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;
    vDanger = pVal->vDanger;

    if( (iDir&1)!=ENGINE_DIR && pJunqi->aInfo[iDir].value>2200 )
    {
        vDanger = 20;
    }
    for(i=0;i<7;i++)
    {
        pChess = &pJunqi->ChessPos[iDir][pDir[i]];
        switch( i )
        {
        case 0:
            if( NONE==pChess->type || pChess->pLineup->isNotLand )
            {
                landFlag1 = 1;
                landFlag2 = 1;
            }
            break;
        case 1:
            if(  NONE==pChess->type || pChess->pLineup->isNotLand )
            {
                landFlag1 = 1;
            }
            break;
        case 2:
            if(  NONE==pChess->type || pChess->pLineup->isNotLand )
            {
                landFlag2 = 1;
            }
            break;
        case 3:
            if(  NONE==pChess->type || pChess->pLineup->isNotLand )
            {
                landFlag3 = 1;
            }
            break;
        default:
            break;
        }

        if( pChess->type!=NONE )
        {
            if((pChess->pLineup->iDir&1)!=(iDir&1))
            {

                if(i<3)
                {
                    value += vDanger<<1;
                    if( pJunqi->aInfo[(iDir+2)&3].bDead &&
                            (iDir&1)==ENGINE_DIR && i>0 )
                    {
                        value += 1000;
                    }
                }
                else if( (iDir&1)==ENGINE_DIR || pChess->pLineup->type<YINGZH )
                {
                    if( pJunqi->aInfo[iDir].value<2100 ||
                           pJunqi->aInfo[(iDir+2)&3].bDead )//todo
                    {

                        //value += 100;
                        if( 3==i && landFlag1 )
                        {
                            value += vDanger;
                        }
                        else if( 4==i && landFlag2 )
                        {
                            value += vDanger;
                        }
                    }
                }
            }
        }
    }

    if( (iDir&1)!=ENGINE_DIR )//todo
    {
        if( landFlag1 )
        {
            log_a("iRpOfst %d %d",pJunqi->iRpOfst,iDir);
            value += vDanger;
        }
        else if( landFlag2 || landFlag3 )
        {
            value += vDanger>>1;
        }
    }
    else
    {
        if( landFlag3 )
        {
            value += 10;
        }
    }


    return value;
}

#if 0
int CheckPathValue(Junqi *pJunqi, int iDir)
{
    int value = 0;
    int val[7] = {0};
    int vLeft = 0;
    int vRight = 0;
    int vDanger = 0;
    u8 bShowFlag;
    u8 bLeft = 0;

    //数值有先后顺序的要求
    u8 aLeft[4] = {4,9,14,19};
    u8 aRight[4] = {0,5,10,15};
    u8 aLeftTriple[3] = {23,29,27};
    u8 aRightTriple[3] = {21,25,27};
    u8 aLeftCorner[2] = {24,22};
    u8 aRightCorner[2] = {20,22};
    u8 aMiddle[2] = {22,27};
    u8 aLeftBarrier[5] = {23,29,27,24,22};
    u8 aRightBarrier[5] = {21,25,27,20,22};

    bShowFlag = pJunqi->aInfo[iDir].bShowFlag;


    val[0] = CalDirPathValue(pJunqi,iDir,aLeft);
    val[1] = CalDirPathValue(pJunqi,iDir,aRight);
    if( bShowFlag )
    {
        if( pJunqi->Lineup[iDir][28].type==JUNQI )
        {
            bLeft = 1;
        }
        else
        {
            bLeft = 0;
        }
        val[2] = CalTripleValue(pJunqi,iDir,aLeftTriple,!bLeft);
        val[3] = CalTripleValue(pJunqi,iDir,aRightTriple,bLeft);
    }
    else
    {
        val[2] = CalTripleValue(pJunqi,iDir,aLeftTriple,0);
        val[3] = CalTripleValue(pJunqi,iDir,aRightTriple,0);
    }

    val[4] = CalCornerValue(pJunqi,iDir,aLeftCorner);
    val[5] = CalCornerValue(pJunqi,iDir,aRightCorner);
    val[6] = CalMiddleValue(pJunqi,iDir,aMiddle);

//    for(int i=0;i<7;i++)
//    {
//        log_a("val %d %d",i,val[i]);
//    }
    vLeft = val[0]+val[2]+val[4];
    vRight = val[1]+val[3]+val[5];
    if( bShowFlag )
    {
        if( bLeft )
        {
            vDanger = CalDangerValue(pJunqi,iDir,aLeftBarrier);
            value = vLeft+(vRight>>1)+val[6]+val[0]+vDanger;
        }
        else
        {
            assert( pJunqi->Lineup[iDir][26].type==JUNQI );
            vDanger = CalDangerValue(pJunqi,iDir,aRightBarrier);
            value = vRight+(vLeft>>1)+val[6]+val[1]+vDanger;
            //log_a("danger %d vRight %d vLeft %d",vDanger,vRight,vLeft>>1);
        }
    }
    else
    {
        value = vLeft+vRight+val[6];
    }
    //log_a("dir %d %d",iDir,value);
    return value;
}
#endif

int CheckDangerValue(Junqi *pJunqi, int iDir)
{
    int vDanger = 0;
    u8 bShowFlag;
   // return vDanger;
    u8 aLeftBarrier[7] = {23,29,27,24,22,20,21};
    u8 aRightBarrier[7] = {21,25,27,20,22,23,24};
    //u8 aBarrier[7] = {21,25,23,20,24,22,29};

    bShowFlag = pJunqi->aInfo[iDir].bShowFlag;

    if( bShowFlag )
    {
        if( pJunqi->Lineup[iDir][28].type==JUNQI )
        {
            vDanger = CalDangerValue(pJunqi,iDir,aLeftBarrier);
        }
        else
        {

            vDanger = CalDangerValue(pJunqi,iDir,aRightBarrier);
        }
    }
//    else if( (iDir&1)!=(ENGINE_DIR&1) )
//    {
//        vDanger = CalDangerValue(pJunqi,iDir,aBarrier);
//    }
    log_a("dir %d vDanger %d",iDir,vDanger);
    return vDanger;
}

int GetConnectValue(Junqi *pJunqi, int iDir)
{
    BoardChess *pSrc;
    BoardChess *pNbr;
    ChessLineup *pLineup;
    int i,j;
    int x,y;
    int value = 0;
    u8 val;

    for(i=0;  i<30; i++)
    {
        pLineup = &pJunqi->Lineup[pJunqi->myTurn][i];
        if( pLineup->bDead || pLineup->type==NONE )
        {
            continue;
        }
        pSrc = pLineup->pChess;

        if( pSrc->isCamp )
        {
            for(j=0; j<9; j++)
            {

                if( j==4 ) continue;
                x = pSrc->point.x+1-j%3;
                y = pSrc->point.y+j/3-1;

                if( pJunqi->aBoard[x][y].pAdjList )
                {
                    pNbr = pJunqi->aBoard[x][y].pAdjList->pChess;
                    if( pNbr->type!=NONE )
                    {
                        if( pNbr->isRailway )
                        {
                            val = 2;
                        }
                        else
                        {
                            val = 1;
                        }
                        if( !pLineup->isNotBomb )
                        {
                            val = val<<1;
                        }
                        value += val;
                    }
                }
            }
        }
    }
    if( iDir%2!=pJunqi->myTurn%2 )
    {
        value = -value;
    }

    return value;
}


int CheckMaxChess(Junqi *pJunqi, int aMaxNum[], int *mxType)
{
    int nMax = 0;
    int rc = 0;
    int num;
    u8 i;
    u8 type;


    for(type=SILING; type<TUANZH; type++)
    {
        nMax = 0;
        for(i=0; i<4; i++)
        {
            if( pJunqi->aInfo[i].bDead ) continue;


            if( (i&1)==(ENGINE_DIR&1) )
            {
                num = pJunqi->aInfo[i].aTypeNum[type];
                nMax += num;

            }
            else
            {
                num = pJunqi->aInfo[i].aLiveAllNum[type] -
                        pJunqi->aInfo[i].aLiveAllNum[type-1];
                nMax -= num;

            }
        }
        log_a("type %d num %d",type,nMax);
        aMaxNum[type] = nMax;
        if( !rc && nMax )
        {
            *mxType = type;
            rc = nMax;
        }
    }

    return rc;
}

void SetMaxType(Junqi *pJunqi)
{
    int num;
    u8 i;
    u8 type;
    u8 aSetFlag[4] = {0};

    for(i=0; i<4; i++)
    {
        pJunqi->aInfo[i].mxType = TUANZH;
    }

    for(type=SILING; type<TUANZH; type++)
    {
        for(i=0; i<4; i++)
        {
            if( pJunqi->aInfo[i].bDead ) continue;
            if( aSetFlag[i] ) continue;


            if( (i&1)==(ENGINE_DIR&1) )
            {
                num = pJunqi->aInfo[i].aTypeNum[type];

            }
            else
            {
                num = pJunqi->aInfo[i].aLiveAllNum[type] -
                        pJunqi->aInfo[i].aLiveAllNum[type-1];
            }
            if( num!=0 )
            {
                pJunqi->aInfo[i].mxType = type;
                aSetFlag[i] = 1;
            }
        }
    }

}


int CalMaxChessValue(Junqi *pJunqi, int aMaxNum[])
{
    int value = 0;
    Engine *pEngine;
    Value_Parameter *pVal;
    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;
    int type;
    int val;

    for(type=SILING; type<TUANZH; type++)
    {
//        if( type>JUNZH )
//        {
//            val = pVal->vChess[type]>>1;
//        }
//        else
//        {
//            val = pVal->vChess[type];
//        }
        val = pVal->vChess[type]>>1;
        log_a("val %d aMaxNum[%d] %d",val,type,aMaxNum[type]);
        value += val*aMaxNum[type];
    }

    return value;
}

void ReSetBombValue(Junqi *pJunqi)
{
    u8 i;
    u8 type;
    int mxType = YINGZH;
    Engine *pEngine;
    Value_Parameter *pVal;


    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;

    for(type=SILING; type<TUANZH; type++)
    {
        for(i=0; i<4; i++)
        {
            if( pJunqi->aInfo[i].bDead ) continue;
            if( mxType==YINGZH )
            {
                mxType = type;
            }
        }
    }
    pVal->vChess[ZHADAN] = gChessValue[ZHADAN]-
            ((gChessValue[SILING]-gChessValue[mxType])>>1);

}

u8 aLeftDeltaLand[5] = {21,23,24,28,29};
u8 aRighDeltaLand[5] = {23,21,20,26,25};
//todo 对时间效率影响很大，从16-》25
int GetDeltaLandValue(Junqi *pJunqi, int iDir, int index)
{
    int value = 0;
    u8 *pIndex;
    Engine *pEngine;
    Value_Parameter *pVal;
    int vLand;

    pEngine = pJunqi->pEngine;
    pVal= &pEngine->valPara;
    vLand = pVal->vChess[DILEI];

    if( !pJunqi->aInfo[iDir].bShowFlag )
    {
        return 0;
    }
    else
    {
        if( pJunqi->Lineup[iDir][26].type==JUNQI  )
        {
            pIndex = &aLeftDeltaLand[0];
        }
        else
        {
            pIndex = &aRighDeltaLand[0];
        }
    }

    if( (iDir&1)!=ENGINE_DIR )
    {
        if( index==pIndex[0] )
        {
            value = 40;
        }
//        else if( index==pIndex[1] || index==pIndex[2] )
//        {
//            value = -20;
//        }
    }
    else
    {
        if( index==pIndex[1] )
        {
            value = 20-vLand;
        }
        else if( index==pIndex[2] || index==pIndex[3] || index==pIndex[4] )
        {
            value = -vLand-20;
        }
    }

    return value;
}


int EvalSituation(Junqi *pJunqi, u8 isInit)
{
	int i,j;
	ChessLineup *pLineup;
	int tempValue = 0;
	int value = 0;;
	Engine *pEngine;
	Value_Parameter *pVal;
	int aMaxNum[14] = {0};
	int vDeltaBomb = 0;
	int rc = 0;
	int vMaxChess = 0;
	int typeValue;
	int mxType = PAIZH;

	pEngine = pJunqi->pEngine;
	pVal= &pEngine->valPara;



	rc = CheckMaxChess(pJunqi,aMaxNum,&mxType);

	if( rc>0 )
	{
	    vDeltaBomb = 30;
	}
	else if( rc<0 )
	{
	    vDeltaBomb = -30;
	}
	log_a("maxTye %d val %d rc %d",mxType,vMaxChess,rc);
	if( pJunqi->iRpOfst<100 )
	{
	    vMaxChess += CalMaxChessValue(pJunqi,aMaxNum);
	}
	log_a("max %d rc %d",vMaxChess,rc);
    value += vMaxChess;
	for(i=0; i<4; i++)
	{
	    tempValue = 0;

		if( !pJunqi->aInfo[i].bDead || !pJunqi->aInfo[i].deadValue )
		{
		    //assert(i==1);

//			log_b("i %d dilei %d zhadan %d",i,
//					pJunqi->aInfo[i].aTypeNum[DILEI],
//					pJunqi->aInfo[i].aTypeNum[ZHADAN]);
			for(j=0; j<30; j++)
			{
				pLineup = &pJunqi->Lineup[i][j];
				if( pLineup->type!=NONE && pLineup->type!=JUNQI )
				{
					if( i%2==ENGINE_DIR%2 )
					{

//					    if(i==1 && j==20)
//					    {
//					        log_a("aaa");
//					    }
						if( pLineup->bDead )
						    //|| (pLineup->pChess->isStronghold && pLineup->pChess->iDir!=i) )
						{
						    typeValue = pVal->vChess[pLineup->type];
							tempValue -= typeValue;
							if( pLineup->type==JUNZH || pLineup->type==SILING )
							{
							    if( 0==pLineup->nEat && ( pJunqi->nEat<20 ||
							            pJunqi->beginValue<0 ) )//todo 防止残局优势时会变得退缩
							    {
							        //tempValue -= (typeValue)>>1;
							        tempValue -= typeValue;
							        //todo  和吃过大子的棋打兑
							        if( pJunqi->iRpOfst<30 && pLineup->nBigEat )
							        {
							            tempValue -= typeValue<<1;
							        }
							    }
							}
							if( pLineup->index>=20 )
							{
								tempValue -= (pVal->vDarkBomb+pVal->vDarkLand);
							}
							else if(  pLineup->index>=5 )
							{
								tempValue -= pVal->vDarkBomb;
							}
							if( pLineup->type==ZHADAN )
							{
							    if( 0!=pJunqi->aInfo[i].aTypeNum[ZHADAN] )
							    {
							        tempValue += vDeltaBomb;//令子多则减少炸弹价值，否则增加炸弹价值
							    }
							    else if( rc<0 )
							    {
							        tempValue += vDeltaBomb+(vDeltaBomb>>2);
							    }

							}
							if( pLineup->type==DILEI )
							{
							    tempValue -= GetDeltaLandValue(pJunqi,i,pLineup->index);
							    if( pJunqi->aInfo[i].value>2000 )
							    {
							        tempValue += (typeValue>>1);
							    }
							}
						}
						else
						{
							if( pLineup->isNotLand && pLineup->index>=20 )
							{
								tempValue -= pVal->vDarkLand;
							}

							if( pLineup->isNotBomb && pLineup->index>=5 )
							{
								tempValue -= pVal->vDarkBomb;
							}
							if( pJunqi->nEat>30  )
							{
							    if( pLineup->type==pJunqi->aInfo[i].mxType &&
							            !pLineup->pChess->isRailway )
							    {
							        tempValue -= 10;
							    }
							}
//							if( pLineup->nEat>1 )
//							{
//							    value += (pLineup->nEat-1)*20;
//							}
						}

					}
					else
					{
						if( pLineup->bDead )
						{
							if( pLineup->type==DARK )
							{

							    if( pLineup->mx_type>TUANZH )//被团长以下的棋暗吃
							    {

							        tempValue += pVal->vChess[pLineup->mx_type];
							    }
							    else
							    {
							        tempValue += pVal->vChess[LVZH]>>1;
							    }

							}
							else
							{
								if( pLineup->bBomb )
								{
								    tempValue += (pVal->vChess[pLineup->type]+
								    	 	(pVal->vChess[ZHADAN]) )/2;
								}
								else if( pLineup->type==GONGB || pLineup->type==DILEI )
								{
									tempValue += pVal->vChess[pLineup->type];
								}
								else
								{
								    tempValue += (pVal->vChess[pLineup->type]+
								    	 	pVal->vChess[pLineup->mx_type])/2;
								}
							}
							//死掉的棋需要加回暗信息分数
							if( pLineup->index>=20 )
							{
								tempValue += (pVal->vDarkBomb+pVal->vDarkLand);
							}
							else if(  pLineup->index>=5 )
							{
								tempValue += pVal->vDarkBomb;
							}

							//这样一改可能敌方炸弹的价值比我方39都要大
//                            if( pLineup->type==ZHADAN )
//                            {
//                                tempValue += vDeltaBomb;//令子多则减少炸弹价值，否则增加炸弹价值
//                            }
                            if( pLineup->type==DILEI )
                            {
                                tempValue += GetDeltaLandValue(pJunqi,i,pLineup->index);
                            }
						}
						else
						{
							if( pLineup->isNotLand && pLineup->index>=20 )
							{
								tempValue += pVal->vDarkLand;
							}
							if( pLineup->isNotBomb && pLineup->index>=5 )
							{
								tempValue += pVal->vDarkBomb;
							}
//                            if( pLineup->nEat>1 )
//                            {
//                                value -= (pLineup->nEat-1)*20;
//                            }
						}
					}

				}
				log_a("i,j %d %d tempValue %d",i,j,tempValue);
			}

            if( i%2==ENGINE_DIR%2 )
            {

                //tempValue -= (CheckDangerValue(pJunqi,i)>>1);
                tempValue -= CheckDangerValue(pJunqi,i);
                tempValue -= CheckCampValue(pJunqi,i);
                if( pJunqi->iRpOfst<100 || (i&1)!=ENGINE_DIR )//todo
                {
                    if( pJunqi->aInfo[i].bShowFlag )
                    {
                        tempValue -= (pVal->vDarkBomb+pVal->vDarkLand);
                        tempValue -= pVal->vDarkJunqi;
                    }
                }
                log_a("temp1 value %d %d",i,tempValue);
                if( pJunqi->aInfo[i].bDead )
                {
//                    if( tempValue>-pVal->vAllChess )
//                    {
//                        tempValue = -(pVal->vAllChess+(pVal->vDanger<<2)+50);
//                    }

                    tempValue = -pJunqi->aInfo[i].value-pVal->vDanger;
                    if( tempValue>-pVal->vAllChess )
                    {
                        tempValue = -pVal->vAllChess;
                    }

                    if( pJunqi->aInfo[(i+2)&3].bDead)
                    {
                        tempValue -= 2000;
                    }
                    pJunqi->aInfo[i].deadValue = tempValue;

                }
                log_a("temp2 value %d %d",i,tempValue);
            }
            else
            {
                tempValue += CheckDangerValue(pJunqi,i);
                tempValue += CheckCampValue(pJunqi,i);
                if( pJunqi->aInfo[i].bShowFlag )
                {
                    tempValue += (pVal->vDarkBomb+pVal->vDarkLand);
                    tempValue += pVal->vDarkJunqi;
                }
                log_a("temp3 value %d %d",i,tempValue);
                if( pJunqi->aInfo[i].bDead )
                {
//                    if( tempValue<pVal->vAllChess )
//                    {
//                        tempValue = pVal->vAllChess+(pVal->vDanger<<2)+50;
//                    }

                    tempValue = pJunqi->aInfo[i].value+pVal->vDanger;
                    if( tempValue<pVal->vAllChess )
                    {
                        tempValue = pVal->vAllChess;
                    }

                    if( pJunqi->aInfo[(i+2)&3].bDead)
                    {
                        tempValue = tempValue+2000;
                    }
                    pJunqi->aInfo[i].deadValue = tempValue;
                }
                log_a("temp4 value %d %d",i,tempValue);
            }

		}
		else
		{
			if( i%2==ENGINE_DIR%2 )
			{
				tempValue = pJunqi->aInfo[i].deadValue;
			}
			else
			{
				tempValue = pJunqi->aInfo[i].deadValue;
			}
			log_a("dead value %d %d",i,tempValue);
		}
		if( isInit )
		{

		    if(i%2==ENGINE_DIR)
		    {
		        pJunqi->aInfo[i].value = -tempValue;
		    }
		    else
		    {
		        pJunqi->aInfo[i].value = tempValue;
		    }
		    log_a("dir %d value %d",i,pJunqi->aInfo[i].value);
		}
		value += tempValue;
	}
    if( isInit )
    {
        pJunqi->beginValue = value;
    }
	return value;
}
