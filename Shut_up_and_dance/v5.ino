// 預寫好sequence 第二首
//colorset
void setupPart_shutUAD(int partNumber) {
    Serial.println(partNumber);

    switch (partNumber) {
        case 1:
            // "Ooh, shut up and dance with me" 開頭 12拍
            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*11)) );

            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
            break;

        case 2:
            // "We were victims of the night" 8拍
            sequence.push_back( //1,2
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*2)
                )
            );
            // sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back( //3
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::LTR(whole, LIGHT_GREEN_3, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //4
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::RTL(whole, YELLOW_3, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //5
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::LTR(body, PURPLE_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //6
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::RTL(body, PURPLE_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            //sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            //sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            //sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME_2*2, 100, 1, 150)) );
            sequence.push_back( //7
                PlayStep::Create(
                    isMe({1, 2, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //8
                PlayStep::Create(
                    isMe({1, 3, 7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            break;

        case 3:
            // "The chemical, physical, kryptonite" 8拍
            sequence.push_back( //1
                PlayStep::Create(
                    isMe({1,3}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //2-4
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*3)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3)
                )
            );
            sequence.push_back( //5-5.5 in the night
                PlayStep::Create(
                    isMe({1,2,3}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            sequence.push_back( //5.5-6
                PlayStep::Create(
                    isMe({1,4,7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );  
            sequence.push_back( //6-8
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            break;

        case 4:
            // "Helpless to the bass and faded light" 8拍
            // 1~2拍：繞一圈
            // 3~4拍：隨機亮
            {
                std::vector<int> circle = {1,3,7,6,5,4,2};
                std::vector<int> random = {4,2,5,1,6,3,7};

                for (int i = 0; i < 7; i++) { //bass and
                    sequence.push_back( PlayStep::Create(
                        isMe({circle[i]}) 
                            ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                            : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                    ));
                }
                for (int i = 0; i < 7; i++) { //faded light
                    sequence.push_back( PlayStep::Create(
                        isMe({random[i]}) 
                            ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                            : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                    ));
                }
            }

            sequence.push_back( PlayStep::Create(Animation::LTR(whole, LIGHT_BLUE_3, BEAT_TIME_2*2)) ); //5-6

            sequence.push_back( //6-7.5 we were
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*1.5)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*1.5)
                )
            );

            sequence.push_back( //7.5-8 (bound)
                PlayStep::Create(
                    isMe({1,2}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            break;

        case 5:
            // "Oh, we were bound to get together, bound to get together"
            sequence.push_back( //1-3.5 (bound)
                PlayStep::Create(
                    isMe({1,2,4}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*3.5)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3.5)
                )
            );  
            sequence.push_back( //3.5-4
                PlayStep::Create(
                    isMe({1,3}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            sequence.push_back( //5-7
                PlayStep::Create(
                    isMe({1,3,7}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2*4)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
                )
            );
            
            //8 拍：隨機亮
            {
                std::vector<int> random2 = {1,2,3};
                for (int i = 0; i < 3; i++) {
                    sequence.push_back( PlayStep::Create(
                        isMe({random2[i]}) 
                            ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3)
                            : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3)
                    ));
                }
            }

            break;

        case 6:
            // "She took my arm, I don't know how it happened"

            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*2)) ); //1-2
            //3 繞一圈
            for (int i = 0; i < 7; i++) {
                sequence.push_back(
                    PlayStep::Create(
                        isMe({1,3,7,6,5,4,2}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/7)
                                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/7)
                    )
                );
            }
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*3)) ); //4-6
            //7-8 亮C
            sequence.push_back(
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*2)
                )
            );

            break;

        // 7-11跟前面同邏輯！要繼續我可以馬上幫你補上
        case 7:
        // "We took the floor and she said"
        //1-4 亮C （rainbow？）
        sequence.push_back(
            PlayStep::Create(
                isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
            )
        );
        //3-4
        sequence.push_back(
            PlayStep::Create(
                isMe({1}) ? Animation::LTR(legs, WHITE_3, BEAT_TIME_2*2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*2)
            )
        );

        // 5～8拍：快速閃爍
        //嘗試閃rainbow
        for (int i = 0; i < 6; i++) {
            sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME_2/6, 100, 5, 100)) );
            sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME_2/6, 150, 5, 100)) );
            sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME_2/6, 200, 5, 100)) );
        }
        /*
        for (int i = 0; i < 12; i++) {
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/12)) );
        }
        */
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        break;

    case 8:
        // "Oh, don't you dare look back, just keep your eyes on me"
        //1,2
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );

        //3-4 隨機亂亮
        sequence.push_back( 
            PlayStep::Create(
                isMe({3,5}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
            )
        );

        sequence.push_back( 
            PlayStep::Create(
                isMe({2,7}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
            )
        );

        sequence.push_back( 
            PlayStep::Create(
                isMe({4,6}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
            )
        );

        sequence.push_back( 
            PlayStep::Create(
                isMe({1}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/2)
                          : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
            )
        );

        // 5～8拍：左到右、右到左波浪效果
        {
            std::vector<int> leftToRight = {7,3,6,1,5,2,4};
            std::vector<int> rightToLeft = {4,2,5,1,6,3,7};

            for (int i = 0; i < 7; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({leftToRight[i]}) 
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }
            
            for (int i = 0; i < 7; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({rightToLeft[i]}) 
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }
        }
        break;

    case 9:
        // "I said, 'You're holding back', she said, 'Shut up and dance with me'"
        {
            for (int i = 0; i < 7; i++) { //1,2
                sequence.push_back( PlayStep::Create(
                    isMe({leftToRight[i]})
                        ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }

            for (int i = 0; i < 7; i++) { //3,4
                sequence.push_back( PlayStep::Create(
                    isMe({rightToLeft[i]}) 
                        ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }

            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) ); //5 (shut) up and
            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
            // "dance with me" 快速閃爍
            for (int i = 0; i < 4; i++) { //7-8
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/6)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/6)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/6)) );
            }

            //sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        }
        break;

    case 10:
        // "This woman is my destiny, she said"
        // destiny要不要對拍點閃人？
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        
        sequence.push_back( PlayStep::Create( //2-8
            isMe({2,3})
                ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*7)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*7)
        ));
        
        break;

    case 11:
        // 1-4 "Ooh, shut up and dance with me"
        sequence.push_back( PlayStep::Create(
            isMe({6})
                ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2*4)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
        ));
        // 5-8
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2 * 2)) ); //給第三首的時間
        break;

        default:
            stopEffect();
            break;
    }
}