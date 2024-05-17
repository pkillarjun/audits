#!/bin/sh

COUNT=1
mkdir nas5g_message_decode_report/

for file in 'nas5g_message_decode_out_corpus/master/crashes/id:000000,sig:06,src:000002,time:6,execs:208,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000001,sig:06,src:000002,time:36,execs:308,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000004,sig:06,src:000002,time:7648,execs:13736,op:havoc,rep:16' 'nas5g_message_decode_out_corpus/master/crashes/id:000005,sig:06,src:000007,time:17631,execs:34140,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000008,sig:06,src:000007,time:18355,execs:44376,op:havoc,rep:16' 'nas5g_message_decode_out_corpus/master/crashes/id:000011,sig:06,src:000009,time:20123,execs:68212,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000012,sig:06,src:000009,time:20328,execs:70649,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000013,sig:06,src:000009,time:20636,execs:74614,op:havoc,rep:4' 'nas5g_message_decode_out_corpus/master/crashes/id:000015,sig:06,src:000009,time:21037,execs:80200,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000017,sig:06,src:000011,time:23161,execs:101558,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000034,sig:06,src:000220+000219,time:152820,execs:311034,op:splice,rep:8' 'nas5g_message_decode_out_corpus/master/crashes/id:000038,sig:06,src:000000,time:193597,execs:351382,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000053,sig:06,src:000311,time:326731,execs:557794,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000062,sig:06,src:000305,time:454419,execs:805976,op:havoc,rep:2' 'nas5g_message_decode_out_corpus/master/crashes/id:000063,sig:06,src:000407,time:474326,execs:845193,op:havoc,rep:4' 'nas5g_message_decode_out_corpus/master/crashes/id:000064,sig:06,src:000407,time:475622,execs:846057,op:havoc,rep:4' 'nas5g_message_decode_out_corpus/master/crashes/id:000087,sig:06,src:000408+000234,time:1896919,execs:3006046,op:splice,rep:4' 'nas5g_message_decode_out_corpus/master/crashes/id:000111,sig:06,src:000410+000246,time:71583028,execs:121600824,op:splice,rep:8' 'nas5g_message_decode_out_corpus/slave1/crashes/id:000053,sig:06,src:000058+000054,time:337026,execs:593141,op:splice,rep:16' 'nas5g_message_decode_out_corpus/slave1/crashes/id:000073,sig:06,src:000312,time:1237976,execs:2461275,op:havoc,rep:4' 'nas5g_message_decode_out_corpus/slave2/crashes/id:000012,sig:06,src:000236,time:172340,execs:255777,op:arith8,pos:9,val:-35' 'nas5g_message_decode_out_corpus/slave2/crashes/id:000016,sig:06,src:000010,time:193823,execs:287528,op:flip2,pos:6'
do
    VAR="nas5g_message_decode_report/bug.$COUNT.raw"
    cp $file $VAR

    ./nas5g_message_decode $VAR |& tee nas5g_message_decode_report.asan

    mv nas5g_message_decode_report.asan "${VAR}.asan"
    let COUNT++
done

