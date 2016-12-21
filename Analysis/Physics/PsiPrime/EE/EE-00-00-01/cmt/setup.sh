# echo "Setting Mumu Mumu-00-00-01 in /afs/ihep.ac.cn/users/c/chenq/WorkArea-664.p03/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=Mumu -version=Mumu-00-00-01 -path=/afs/ihep.ac.cn/users/c/chenq/WorkArea-664.p03/Analysis  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

