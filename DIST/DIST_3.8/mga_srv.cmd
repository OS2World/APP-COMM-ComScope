/* copy newest versions */
'@echo off'
say ''
say 'Copying Distribution Versions'
say ''
say '-------- Configuration --------'
say 'COMi_CFG.DLL'
'copy \results\COMI_CFG.DLL > NUL'
say '-------- Spooler --------'
say 'COMi_SPL.PDR'
'copy f:\projects\results\COMi_SPL.DLL COMi_SPL.PDR > NUL'
say 'SPL_DEMO.PDR'
'copy f:\projects\results\SPL_DEMO.DLL SPL_DEMO.PDR > NUL'
say '-------- Runtime library ------'
say 'OS2LSRTL.DLL'
'copy f:\projects\results\OS2LSRTL.DLL > NUL'
say '-------- Utilities ----------'
say 'OS2LS_IO.DLL'
'copy f:\projects\results\OS2LS_IO.DLL > NUL'
say 'OS2LS_PR.DLL'
'copy f:\projects\results\OS2LS_PR.DLL > NUL'
say 'OS2LS_UT.DLL'
'copy f:\projects\results\OS2LS_UT.DLL > NUL'
say 'COMi_CTL.DLL'
'copy f:\projects\results\COMi_CTL.DLL > NUL'
say '-------- COMscope --------'
say 'COMscope.EXE'
'copy f:\projects\COMscope\results\COMscope.EXE > NUL'
say 'CSDEMO.EXE'
'copy f:\projects\COMscope\DEMO\CSDEMO.EXE > NUL'
say 'COMscope.HLP -> CSDEMO.HLP'
'copy f:\projects\help\Comscope.HLP \help\CSDEMO.HLP > NUL'
say '-------- Install --------'
say 'INSTALL.EXE'
'copy f:\projects\install\results\INSTALL.EXE > NUL'
say 'PDA_INST.DLL'
'copy f:\projects\results\pda_inst.dll > NUL'
say 'PDB_INST.DLL'
'copy f:\projects\results\pdb_inst.dll > NUL'
say ''
