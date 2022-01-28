axel -n 20 -o "osdi.tar.xz" "https://uc40bb10915b15f8b708ca0758df.dl.dropboxusercontent.com/cd/0/get/BY9ea_Ejek1eaqLMwab5NfTa1HuY3c3KH85KHHElmXtvewoa044pd675KqEzVnIhetczh1RT-uwPnNV68ckEfJvdMT_TRhT0u_vP6aussE1btxSIrsIGtMRsLuAJ1Bejig78vIis6_oXv63SG_cgt0b8/file?_download_id=2853179608333043795605159794376514451237318437459082882440850957&_notify_domain=www.dropbox.com&dl=1"
tar -xvf osdi.tar.xz
rm osdi.tar.xz

axel -n 20 -o "cdt-stand-alone-debugger.tar.gz" "https://mirror.library.ucy.ac.cy/eclipse/tools/cdt/releases/10.1/cdt-10.1.0/rcp/cdt-stand-alone-debugger-10.1.0-20201211-1436-linux.gtk.x86_64.tar.gz"
tar zxvf cdt-stand-alone-debugger.tar.gz
rm cdt-stand-alone-debugger.tar.gz
