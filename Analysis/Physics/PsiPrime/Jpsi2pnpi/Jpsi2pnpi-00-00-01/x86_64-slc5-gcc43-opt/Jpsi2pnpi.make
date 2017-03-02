#-- start of make_header -----------------

#====================================
#  Library Jpsi2pnpi
#
#   Generated Tue Feb 21 22:05:35 2017  by kiuchi
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Jpsi2pnpi_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Jpsi2pnpi_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Jpsi2pnpi

Jpsi2pnpi_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_Jpsi2pnpi = /tmp/CMT_$(Jpsi2pnpi_tag)_Jpsi2pnpi.make$(cmt_lock_pid)
else
#cmt_local_tagfile_Jpsi2pnpi = $(Jpsi2pnpi_tag)_Jpsi2pnpi.make
cmt_local_tagfile_Jpsi2pnpi = $(bin)$(Jpsi2pnpi_tag)_Jpsi2pnpi.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

Jpsi2pnpi_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_Jpsi2pnpi = /tmp/CMT_$(Jpsi2pnpi_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_Jpsi2pnpi = $(Jpsi2pnpi_tag).make
cmt_local_tagfile_Jpsi2pnpi = $(bin)$(Jpsi2pnpi_tag).make
endif

endif

-include $(cmt_local_tagfile_Jpsi2pnpi)

ifdef cmt_Jpsi2pnpi_has_target_tag

ifdef READONLY
cmt_final_setup_Jpsi2pnpi = /tmp/CMT_Jpsi2pnpi_Jpsi2pnpisetup.make
cmt_local_Jpsi2pnpi_makefile = /tmp/CMT_Jpsi2pnpi$(cmt_lock_pid).make
else
cmt_final_setup_Jpsi2pnpi = $(bin)Jpsi2pnpi_Jpsi2pnpisetup.make
cmt_local_Jpsi2pnpi_makefile = $(bin)Jpsi2pnpi.make
endif

else

ifdef READONLY
cmt_final_setup_Jpsi2pnpi = /tmp/CMT_Jpsi2pnpisetup.make
cmt_local_Jpsi2pnpi_makefile = /tmp/CMT_Jpsi2pnpi$(cmt_lock_pid).make
else
cmt_final_setup_Jpsi2pnpi = $(bin)Jpsi2pnpisetup.make
cmt_local_Jpsi2pnpi_makefile = $(bin)Jpsi2pnpi.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_Jpsi2pnpisetup.make
else
cmt_final_setup = $(bin)Jpsi2pnpisetup.make
endif

Jpsi2pnpi ::


ifdef READONLY
Jpsi2pnpi ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Jpsi2pnpi'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Jpsi2pnpi/
Jpsi2pnpi::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

Jpsi2pnpilibname   = $(bin)$(library_prefix)Jpsi2pnpi$(library_suffix)
Jpsi2pnpilib       = $(Jpsi2pnpilibname).a
Jpsi2pnpistamp     = $(bin)Jpsi2pnpi.stamp
Jpsi2pnpishstamp   = $(bin)Jpsi2pnpi.shstamp

Jpsi2pnpi :: dirs  Jpsi2pnpiLIB
	$(echo) "Jpsi2pnpi ok"

#-- end of libary_header ----------------

Jpsi2pnpiLIB :: $(Jpsi2pnpilib) $(Jpsi2pnpishstamp)
	@/bin/echo "------> Jpsi2pnpi : library ok"

$(Jpsi2pnpilib) :: $(bin)Jpsi2pnpi.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Jpsi2pnpilib) $?
	$(lib_silent) $(ranlib) $(Jpsi2pnpilib)
	$(lib_silent) cat /dev/null >$(Jpsi2pnpistamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Jpsi2pnpilibname).$(shlibsuffix) :: $(Jpsi2pnpilib) $(Jpsi2pnpistamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Jpsi2pnpi $(Jpsi2pnpi_shlibflags)

$(Jpsi2pnpishstamp) :: $(Jpsi2pnpilibname).$(shlibsuffix)
	@if test -f $(Jpsi2pnpilibname).$(shlibsuffix) ; then cat /dev/null >$(Jpsi2pnpishstamp) ; fi

Jpsi2pnpiclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Jpsi2pnpi.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
Jpsi2pnpiinstallname = $(library_prefix)Jpsi2pnpi$(library_suffix).$(shlibsuffix)

Jpsi2pnpi :: Jpsi2pnpiinstall

install :: Jpsi2pnpiinstall

Jpsi2pnpiinstall :: $(install_dir)/$(Jpsi2pnpiinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Jpsi2pnpiinstallname) :: $(bin)$(Jpsi2pnpiinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Jpsi2pnpiinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Jpsi2pnpiinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Jpsi2pnpiinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Jpsi2pnpiinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Jpsi2pnpiinstallname) $(install_dir)/$(Jpsi2pnpiinstallname); \
	      echo `pwd`/$(Jpsi2pnpiinstallname) >$(install_dir)/$(Jpsi2pnpiinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Jpsi2pnpiinstallname), no installation directory specified"; \
	  fi; \
	fi

Jpsi2pnpiclean :: Jpsi2pnpiuninstall

uninstall :: Jpsi2pnpiuninstall

Jpsi2pnpiuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Jpsi2pnpiinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Jpsi2pnpiinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Jpsi2pnpiinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Jpsi2pnpiinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),Jpsi2pnpiclean)

#$(bin)Jpsi2pnpi_dependencies.make :: dirs

ifndef QUICK
$(bin)Jpsi2pnpi_dependencies.make : ../src/Jpsi2pnpi.cc $(use_requirements) $(cmt_final_setup_Jpsi2pnpi)
	$(echo) "(Jpsi2pnpi.make) Rebuilding $@"; \
	  $(build_dependencies) Jpsi2pnpi -all_sources -out=$@ ../src/Jpsi2pnpi.cc
endif

#$(Jpsi2pnpi_dependencies)

-include $(bin)Jpsi2pnpi_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)Jpsi2pnpi_dependencies.make : $(Jpsi2pnpi_cc_dependencies)

$(bin)$(binobj)Jpsi2pnpi.o : $(Jpsi2pnpi_cc_dependencies)
	$(cpp_echo) $(src)Jpsi2pnpi.cc
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(Jpsi2pnpi_pp_cppflags) $(lib_Jpsi2pnpi_pp_cppflags) $(Jpsi2pnpi_pp_cppflags) $(use_cppflags) $(Jpsi2pnpi_cppflags) $(lib_Jpsi2pnpi_cppflags) $(Jpsi2pnpi_cppflags) $(Jpsi2pnpi_cc_cppflags)  $(src)Jpsi2pnpi.cc

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Jpsi2pnpiclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Jpsi2pnpi.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(Jpsi2pnpi.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_Jpsi2pnpi)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsi2pnpi.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsi2pnpi.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsi2pnpi.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

Jpsi2pnpiclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)Jpsi2pnpi$(library_suffix).a $(binobj)$(library_prefix)Jpsi2pnpi$(library_suffix).s? $(binobj)Jpsi2pnpi.stamp $(binobj)Jpsi2pnpi.shstamp
#-- end of cleanup_library ---------------

