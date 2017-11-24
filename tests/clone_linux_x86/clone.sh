#!/bin/sh

tw=8
dt_count=5
base=${0%/clone.sh}
fname=${1##*/}   #just the filename
dir=/tmp
striped_fname=$dir/striped_$fname
prefix=$dir/$fname
weight_fname=$dir/weight_info_$fname
aug_fname=$dir/aug_$fname
splitted_fname=$dir/$fname.cnf
dtree_fname=$dir/$fname.dtree
nnf_fname=$aug_fname.nnf
clone_fname=$dir/$fname.map
ls_fname=${fname}.clone_ls_out.txt

#echo input filename:$fname

#echo striping
java -cp ${base}/preprocess.jar CreateStripedInstance $1 $striped_fname $weight_fname
    
#echo splitting
java -cp ${base}/releaseAll.jar mark.reason.apps.WCnfSplit $tw $1 $prefix -weighted -clauselength -seed 17867931 -numOrders 3 2>&1 >/dev/null
X=$?

if [ $X != 0 ]
then
  echo c Variable splitting failed [exit code = $X].
  rm -f $striped_fname $weight_fname $aug_fname $splitted_fname $dtree_fname $nnf_fname $clone_fname 
  exit $X
fi

#echo augmenting
java -cp ${base}/preprocess.jar CreateAugmentedInstance $splitted_fname $aug_fname $weight_fname

#echo compiling
${base}/c2d_linux -in $aug_fname -smooth_all -dt_count $dt_count -dt_method 4 -reduce 2>&1 >/dev/null #-dt_in $dtree_fname

if [ $X != 0 ]
then 
    echo c Compilation failed [exit code = $X].
    rm -f $striped_fname $weight_fname $aug_fname $splitted_fname $dtree_fname $nnf_fname $clone_fname
    exit $X
fi

#echo solving
${base}/clone -nnf $nnf_fname -w $weight_fname -c $clone_fname -o $1
X=$?

#Clean up
rm -f $striped_fname $weight_fname $aug_fname $splitted_fname $dtree_fname $nnf_fname $clone_fname $ls_fname
exit $X
