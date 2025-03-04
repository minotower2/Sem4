mkdir -p results; echo "" > results.txt
echo "Task1" >> results.txt
./a01.out testing/task1.txt results/out_1_1.txt "aaaaaa bbbbbb_ababab" " _" 1 >> results.txt
./a01.out testing/task1.txt results/out_1_2.txt "aaaaaa bbbbbb_ababab" " _" 2 >> results.txt
./a01.out testing/task1.txt results/out_1_3.txt "aaaaaa bbbbbb_ababab" " _" 3 >> results.txt
./a01.out testing/code1.txt results/out_1_4.txt "{ }" " " 2 >> results.txt
./a01.out testing/code1.txt results/out_1_5.txt "{ }" " " 3 >> results.txt
./a01.out testing/code1.txt results/out_1_6.txt "[ ]" "qwertyuiopasdfghjklzxcvbnm " 4 >> results.txt
./a01.out testing/code1.txt results/out_1_7.txt "i printf if" "(){}[] ;,.+-*=/" 1 >> results.txt
./a01.out testing/code1.txt results/out_1_8.txt "i printf if" "(){}[] ;,.+-*=/" 2 >> results.txt
./a01.out testing/code1.txt results/out_1_9.txt "i printf if" "(){}[] ;,.+-*=/" 5 >> results.txt
./a01.out testing/code1.txt results/out_1_10.txt "else class" "(){}[] ;,.+-*=/" 1 >> results.txt
./a01.out testing/code1.txt results/out_1_11.txt "else class" "(){}[] ;,.+-*=/" 2 >> results.txt
./a01.out testing/code1.txt results/out_1_12.txt "else class" "(){}[] ;,.+-*=/" 5 >> results.txt
./a01.out testing/code1.txt results/out_1_13.txt "<< >>" "(){}[] ;,.+-*=/" 2 >> results.txt
echo "Task2" >> results.txt
./a02.out testing/task2.txt results/out_2_1.txt "apple orange " " _" >> results.txt
./a02.out testing/task2.txt results/out_2_2.txt "apple pineapple" " _" >> results.txt
./a02.out testing/task2.txt results/out_2_3.txt "apple" " _" >> results.txt
./a02.out testing/task2a.txt results/out_2_4.txt "a" " _"  >> results.txt
./a02.out testing/task2a.txt results/out_2_5.txt "_ _a_aa " " _"  >> results.txt
./a02.out testing/task2a.txt results/out_2_6.txt "b___a_aa " " _"  >> results.txt
./a02.out testing/task2a.txt results/out_2_7.txt "_ _a __ b _" " _"  >> results.txt
./a02.out testing/code1.txt results/out_2_8.txt "{ }" " " >> results.txt
./a02.out testing/code1.txt results/out_2_9.txt "[ ]" "qwertyuiopasdfghjklzxcvbnm " >> results.txt
./a02.out testing/code1.txt results/out_2_10.txt "i printf if" "(){}[] ;,.+-*=/" >> results.txt
./a02.out testing/code1.txt results/out_2_11.txt "else class" "(){}[] ;,.+-*=/"  >> results.txt
./a02.out testing/code1.txt results/out_2_12.txt "<< >>" "(){}[] ;,.+-*=/" >> results.txt
echo "Task3" >> results.txt
./a03.out testing/task1.txt  results/out_3_1.txt "_ _a __ b _" " _" " A___ B                    "  >> results.txt
./a03.out testing/task1.txt  results/out_3_3.txt "aaaaa" " _" "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"  >> results.txt
./a03.out testing/task1.txt  results/out_3_4.txt "_ _ababab __ aaaaaaaaaaaa bbbbbbbbbbbb _" " _" ""  >> results.txt
./a03.out testing/task1.txt  results/out_3_5.txt "_ _abababa __  _" " _" "  _t__hi hi hi hi hi          __   "  >> results.txt
./a03.out testing/task2a.txt results/out_3_6.txt "_ _b _" " _" "BOLSHOYBOGACHEVWORD*******************************************************************************************************************"  >> results.txt
./a03.out testing/code1.txt results/out_3_7.txt "{ }" " " "( )">> results.txt
./a03.out testing/code1.txt results/out_3_8.txt "[ ]" "qwertyuiopasdfghjklzxcvbnm " "( )">> results.txt
./a03.out testing/code1.txt results/out_3_9.txt "i printf if" "(){}[] ;,.+-*=/" "tam pam sham">> results.txt
./a03.out testing/code1.txt results/out_3_10.txt "else class" "(){}[] ;,.+-*=/" "emmm" >> results.txt
./a03.out testing/code1.txt results/out_3_11.txt "<< >>" "(){}[] ;,.+-*=/" "" >> results.txt
echo "Task4" >> results.txt
./a04.out testing/task1.txt results/out_4_1.txt "_ aaaaaaaaa bbbbbbbbb __  _" " _" "  =_ = "  >> results.txt
./a04.out testing/task1.txt results/out_4_2.txt "_ bbbbbba abab aaaa __  _" " _" "  >_ = =_"  >> results.txt
./a04.out testing/task1.txt results/out_4_3.txt "_ BOLSHOYBOGACHEVWORD******************************************************************************************************************* BOLSHOYBOGACHEVWORD******************************************************************************************************************* __  _" " _" "  =_ <> "  >> results.txt
./a04.out testing/task1.txt results/out_4_4.txt "_ aa __  _" " _" "  >_ "  >> results.txt
./a04.out testing/task1.txt results/out_4_5.txt "_ a__  _" " _" "  >_  "  >> results.txt
./a04.out testing/task2.txt results/out_4_6.txt "apple orange " " _" "= =" >> results.txt
./a04.out testing/task2.txt results/out_4_7.txt "apple pineapple" " _" "= =" >> results.txt
./a04.out testing/task2.txt results/out_4_8.txt "apple" " _" "=">> results.txt
./a04.out testing/task2a.txt results/out_4_9.txt "a" " _" "= " >> results.txt
./a04.out testing/task2a.txt results/out_4_10.txt "_ _a_aa " " _" "= =" >> results.txt
./a04.out testing/task2a.txt results/out_4_11.txt "b___a_aa " " _" "= = =" >> results.txt
./a04.out testing/task2a.txt results/out_4_12.txt "_ _a __ b _" " _" "= =" >> results.txt
./a04.out testing/code1.txt results/out_4_13.txt "[ ]" "qwertyuiopasdfghjklzxcvbnm " "= =">> results.txt
./a04.out testing/code1.txt results/out_4_14.txt "[ ]" "qwertyuiopasdfghjklzxcvbnm " "= >">> results.txt
./a04.out testing/code1.txt results/out_4_15.txt "if class else" "(){}[]+-/* " "> = <">> results.txt
echo "Task5" >> results.txt
./a05.out testing/task1.txt results/out_5_1.txt "_ aaaaaaaaa bbbbbbbbb __  _" " _" "  =_ = "  >> results.txt
./a05.out testing/task1.txt results/out_5_2.txt "_ bbbbbba abab aaaa __  _" " _" "  >_ = =_"  >> results.txt
./a05.out testing/task1.txt results/out_5_3.txt "_ BOLSHOYBOGACHEVWORD******************************************************************************************************************* BOLSHOYBOGACHEVWORD******************************************************************************************************************* __  _" " _" "  =_ <> "  >> results.txt
./a05.out testing/task1.txt results/out_5_4.txt "_ aa __  _" " _" "  >_ "  >> results.txt
./a05.out testing/task1.txt results/out_5_5.txt "_ a__  _" " _" "  >_  "  >> results.txt
./a05.out testing/task2.txt results/out_5_6.txt "apple orange " " _" "= =" >> results.txt
./a05.out testing/task2.txt results/out_5_7.txt "apple pineapple" " _" "= =" >> results.txt
./a05.out testing/task2.txt results/out_5_8.txt "apple" " _" "=">> results.txt
./a05.out testing/task2a.txt results/out_5_9.txt "a" " _" "= " >> results.txt
./a05.out testing/task2a.txt results/out_5_10.txt "_ _a_aa " " _" "= =" >> results.txt
./a05.out testing/task2a.txt results/out_5_11.txt "b___a_aa " " _" "= = =" >> results.txt
./a05.out testing/task2a.txt results/out_5_12.txt "_ _a __ b _" " _" "= =" >> results.txt
./a05.out testing/code1.txt results/out_5_13.txt "=" "qwertyuiopasdfghjklzxcvbnm " ">">> results.txt
./a05.out testing/code1.txt results/out_5_14.txt "! )" "qwertyuiopasdfghjklzxcvbnm " "> <">> results.txt
./a05.out testing/code1.txt results/out_5_15.txt "if class else" "(){}[]+-/* " "> = <">> results.txt
./a05.out testing/task1.txt results/out_5_16.txt "_ a __ aa _" " _" "  >=_ <>"  >> results.txt
echo "Task6" >> results.txt
./a06.out testing/code1.txt results/out_6_1.txt "p_i_tf data cursor i _" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_2.txt "p_i_tf _p_i_tf" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_3.txt "_ __ ___" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_4.txt "____" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_5.txt "_ha_" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_6.txt "{" " " >> results.txt
./a06.out testing/code1.txt results/out_6_7.txt "}" " " >> results.txt
./a06.out testing/code1.txt results/out_6_8.txt "_l_s_" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_9.txt "_ls_" "(){}[] ;,.+-*=/" >> results.txt
./a06.out testing/code1.txt results/out_6_10.txt "i_" "(){}[] ;,.+-*=/" >> results.txt
echo "Task7" >> results.txt
./a07.out testing/code1.txt results/out_7_1.txt "p%i%tf data cursor i" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_2.txt "%p%i%tf" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_3.txt "% %% %%%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_4.txt "%%%%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_5.txt "%ha%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_6.txt "{" " " >> results.txt
./a07.out testing/code1.txt results/out_7_7.txt "}" " " >> results.txt
./a07.out testing/code1.txt results/out_7_8.txt "%l%s%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_9.txt "%ls%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_10.txt "i%" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/code1.txt results/out_7_11.txt "p%i%tf data cursor i %" "(){}[] ;,.+-*=/" >> results.txt
./a07.out testing/task1.txt results/out_7_12.txt "%" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_13.txt "a%ab%" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_14.txt "a%aa" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_15.txt "a%aa%a" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_16.txt "a%aaa%aaa%" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_17.txt "%a%ab%" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_18.txt "%a%aa" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_19.txt "%a%aa%a" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_20.txt "%a%aaa%aaa%" " _" >> results.txt
./a07.out testing/task1.txt results/out_7_21.txt "%a%aaa%aaa% %a%ab%" " _" >> results.txt
echo "Task8" >> results.txt
./a08.out testing/code1.txt results/out_8_1.txt "[a-z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_2.txt "[a-z][a-z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_3.txt "[a-z][a-z][a-z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_4.txt "[a-z][a-z][a-z][a-z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_5.txt "p[a-z][a-z][a-z]tf i[a-z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_6.txt "c[a-z][a-z][a-z]s" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_7.txt "[a-z]l[a-z]e" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_8.txt "[A-Z]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_9.txt "[0-9][0-9][0-9]" "(){} ;,.+*=/" >> results.txt
./a08.out testing/code1.txt results/out_8_10.txt "\[[0-9]\]" "(){} ;,.+*=/" >> results.txt
echo "Task9" >> results.txt
./a09.out testing/code1.txt results/out_9_1.txt "[^a-z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_2.txt "[^a-z][^a-z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_3.txt "[^a-z][^a-z][^a-z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_4.txt "[^a-z][^a-z][^a-z][^a-z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_5.txt "p[^a-z][^a-z][^a-z]tf i[^a-z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_6.txt "c[^a-z][^a-z][^a-z]s" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_7.txt "[^a-z]l[^a-z]e" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_8.txt "[^A-Z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_9.txt "print[^A-Z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_10.txt "i[^A-Z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_11.txt "clas[^A-Z]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_12.txt "s[^A-Z]ru[^A-Z]t" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_13.txt "[^0-9][^0-9][^0-9][^0-9][^0-9]" "(){} ;,.+*=/" >> results.txt
./a09.out testing/code1.txt results/out_9_14.txt '[^0-9][^0-9][^0-9]\[[^a-z]\] [^0-9]' "(){} ;,.+*=/" >> results.txt
