//
// Created by yue on 2024/3/18.
//

#include "spwm.h"
#include "tim.h"

/**
 * 定时器中断回调函数 定时器周期: 1ms
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint16_t spwm_cnt;   // SPWM数组下标

    /* SPWM */
    if (htim->Instance == TIM1)
    {
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, spwm_list_50[spwm_cnt++]);
        if(spwm_cnt >= SPWM_50)
        {
            spwm_cnt = 0;
        }
    }
}

uint16_t spwm_list_50[SPWM_50] = {
        360,361,362,363,364,365,366,367,369,370,371,372,373,374,375,376,
        378,379,380,381,382,383,384,385,387,388,389,390,391,392,393,395,
        396,397,398,399,400,401,402,403,405,406,407,408,409,410,411,412,
        414,415,416,417,418,419,420,421,423,424,425,426,427,428,429,430,
        431,433,434,435,436,437,438,439,440,441,442,444,445,446,447,448,
        449,450,451,452,453,454,456,457,458,459,460,461,462,463,464,465,
        466,468,469,470,471,472,473,474,475,476,477,478,479,480,481,483,
        484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,
        500,501,502,504,505,506,507,508,509,510,511,512,513,514,515,516,
        517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,
        533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,
        549,550,550,551,552,553,554,555,556,557,558,559,560,561,562,563,
        564,565,566,567,567,568,569,570,571,572,573,574,575,576,577,577,
        578,579,580,581,582,583,584,585,585,586,587,588,589,590,591,592,
        592,593,594,595,596,597,598,598,599,600,601,602,603,603,604,605,
        606,607,608,608,609,610,611,612,612,613,614,615,616,616,617,618,
        619,620,620,621,622,623,623,624,625,626,627,627,628,629,630,630,
        631,632,633,633,634,635,635,636,637,638,638,639,640,640,641,642,
        643,643,644,645,645,646,647,647,648,649,649,650,651,651,652,653,
        653,654,655,655,656,657,657,658,659,659,660,660,661,662,662,663,
        663,664,665,665,666,666,667,668,668,669,669,670,671,671,672,672,
        673,673,674,674,675,676,676,677,677,678,678,679,679,680,680,681,
        681,682,682,683,683,684,684,685,685,686,686,687,687,688,688,689,
        689,689,690,690,691,691,692,692,693,693,693,694,694,695,695,695,
        696,696,697,697,697,698,698,699,699,699,700,700,700,701,701,702,
        702,702,703,703,703,704,704,704,705,705,705,706,706,706,706,707,
        707,707,708,708,708,708,709,709,709,710,710,710,710,711,711,711,
        711,712,712,712,712,712,713,713,713,713,714,714,714,714,714,715,
        715,715,715,715,715,716,716,716,716,716,716,717,717,717,717,717,
        717,717,717,718,718,718,718,718,718,718,718,718,718,719,719,719,
        719,719,719,719,719,719,719,719,719,719,719,719,719,719,719,719,
        719,719,719,719,720,719,719,719,719,719,719,719,719,719,719,719,
        719,719,719,719,719,719,719,719,719,719,719,719,718,718,718,718,
        718,718,718,718,718,718,717,717,717,717,717,717,717,717,716,716,
        716,716,716,716,715,715,715,715,715,715,714,714,714,714,714,713,
        713,713,713,712,712,712,712,712,711,711,711,711,710,710,710,710,
        709,709,709,708,708,708,708,707,707,707,706,706,706,706,705,705,
        705,704,704,704,703,703,703,702,702,702,701,701,700,700,700,699,
        699,699,698,698,697,697,697,696,696,695,695,695,694,694,693,693,
        693,692,692,691,691,690,690,689,689,689,688,688,687,687,686,686,
        685,685,684,684,683,683,682,682,681,681,680,680,679,679,678,678,
        677,677,676,676,675,674,674,673,673,672,672,671,671,670,669,669,
        668,668,667,666,666,665,665,664,663,663,662,662,661,660,660,659,
        659,658,657,657,656,655,655,654,653,653,652,651,651,650,649,649,
        648,647,647,646,645,645,644,643,643,642,641,640,640,639,638,638,
        637,636,635,635,634,633,633,632,631,630,630,629,628,627,627,626,
        625,624,623,623,622,621,620,620,619,618,617,616,616,615,614,613,
        612,612,611,610,609,608,608,607,606,605,604,603,603,602,601,600,
        599,598,598,597,596,595,594,593,592,592,591,590,589,588,587,586,
        585,585,584,583,582,581,580,579,578,577,577,576,575,574,573,572,
        571,570,569,568,567,567,566,565,564,563,562,561,560,559,558,557,
        556,555,554,553,552,551,550,550,549,548,547,546,545,544,543,542,
        541,540,539,538,537,536,535,534,533,532,531,530,529,528,527,526,
        525,524,523,522,521,520,519,518,517,516,515,514,513,512,511,510,
        509,508,507,506,505,504,502,501,500,499,498,497,496,495,494,493,
        492,491,490,489,488,487,486,485,484,483,481,480,479,478,477,476,
        475,474,473,472,471,470,469,468,466,465,464,463,462,461,460,459,
        458,457,456,454,453,452,451,450,449,448,447,446,445,444,442,441,
        440,439,438,437,436,435,434,433,431,430,429,428,427,426,425,424,
        423,421,420,419,418,417,416,415,414,412,411,410,409,408,407,406,
        405,403,402,401,400,399,398,397,396,395,393,392,391,390,389,388,
        387,385,384,383,382,381,380,379,378,376,375,374,373,372,371,370,
        369,367,366,365,364,363,362,361,360,358,357,356,355,354,353,352,
        350,349,348,347,346,345,344,343,341,340,339,338,337,336,335,334,
        332,331,330,329,328,327,326,324,323,322,321,320,319,318,317,316,
        314,313,312,311,310,309,308,307,305,304,303,302,301,300,299,298,
        296,295,294,293,292,291,290,289,288,286,285,284,283,282,281,280,
        279,278,277,275,274,273,272,271,270,269,268,267,266,265,263,262,
        261,260,259,258,257,256,255,254,253,251,250,249,248,247,246,245,
        244,243,242,241,240,239,238,236,235,234,233,232,231,230,229,228,
        227,226,225,224,223,222,221,220,219,218,217,215,214,213,212,211,
        210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,
        194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,
        178,177,176,175,174,173,172,171,170,169,169,168,167,166,165,164,
        163,162,161,160,159,158,157,156,155,154,153,152,152,151,150,149,
        148,147,146,145,144,143,142,142,141,140,139,138,137,136,135,134,
        134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,121,
        120,119,118,117,116,116,115,114,113,112,111,111,110,109,108,107,
        107,106,105,104,103,103,102,101,100,99,99,98,97,96,96,95,
        94,93,92,92,91,90,89,89,88,87,86,86,85,84,84,83,
        82,81,81,80,79,79,78,77,76,76,75,74,74,73,72,72,
        71,70,70,69,68,68,67,66,66,65,64,64,63,62,62,61,
        60,60,59,59,58,57,57,56,56,55,54,54,53,53,52,51,
        51,50,50,49,48,48,47,47,46,46,45,45,44,43,43,42,
        42,41,41,40,40,39,39,38,38,37,37,36,36,35,35,34,
        34,33,33,32,32,31,31,30,30,30,29,29,28,28,27,27,
        26,26,26,25,25,24,24,24,23,23,22,22,22,21,21,20,
        20,20,19,19,19,18,18,17,17,17,16,16,16,15,15,15,
        14,14,14,13,13,13,13,12,12,12,11,11,11,11,10,10,
        10,9,9,9,9,8,8,8,8,7,7,7,7,7,6,6,
        6,6,5,5,5,5,5,4,4,4,4,4,4,3,3,3,
        3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,
        1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,
        2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,
        4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,
        8,8,8,8,9,9,9,9,10,10,10,11,11,11,11,12,
        12,12,13,13,13,13,14,14,14,15,15,15,16,16,16,17,
        17,17,18,18,19,19,19,20,20,20,21,21,22,22,22,23,
        23,24,24,24,25,25,26,26,26,27,27,28,28,29,29,30,
        30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,
        38,38,39,39,40,40,41,41,42,42,43,43,44,45,45,46,
        46,47,47,48,48,49,50,50,51,51,52,53,53,54,54,55,
        56,56,57,57,58,59,59,60,60,61,62,62,63,64,64,65,
        66,66,67,68,68,69,70,70,71,72,72,73,74,74,75,76,
        76,77,78,79,79,80,81,81,82,83,84,84,85,86,86,87,
        88,89,89,90,91,92,92,93,94,95,96,96,97,98,99,99,
        100,101,102,103,103,104,105,106,107,107,108,109,110,111,111,112,
        113,114,115,116,116,117,118,119,120,121,121,122,123,124,125,126,
        127,127,128,129,130,131,132,133,134,134,135,136,137,138,139,140,
        141,142,142,143,144,145,146,147,148,149,150,151,152,152,153,154,
        155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,169,
        170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,
        186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,
        202,203,204,205,206,207,208,209,210,211,212,213,214,215,217,218,
        219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,
        235,236,238,239,240,241,242,243,244,245,246,247,248,249,250,251,
        253,254,255,256,257,258,259,260,261,262,263,265,266,267,268,269,
        270,271,272,273,274,275,277,278,279,280,281,282,283,284,285,286,
        288,289,290,291,292,293,294,295,296,298,299,300,301,302,303,304,
        305,307,308,309,310,311,312,313,314,316,317,318,319,320,321,322,
        323,324,326,327,328,329,330,331,332,334,335,336,337,338,339,340,
        341,343,344,345,346,347,348,349,350,352,353,354,355,356,357,358
};
