HANDLE ExecuteProcess( const string & CommandLine, const string & WorkDir )
{
   STARTUPINFOA sStartInfo;
   ZeroMemory( &sStartInfo, sizeof(STARTUPINFO) );
   sStartInfo.cb = sizeof(STARTUPINFO);
   sStartInfo.wShowWindow = SW_SHOWDEFAULT;
   sStartInfo.dwFlags = STARTF_USESHOWWINDOW;

   PROCESS_INFORMATION sProcessInfo;
   ZeroMemory( &sProcessInfo, sizeof(PROCESS_INFORMATION) );

   BOOL ok = CreateProcessA( NULL, (char*)CommandLine.c_str(),
                           NULL, NULL, true,
                           NORMAL_PRIORITY_CLASS, NULL, WorkDir.c_str() , &sStartInfo, &sProcessInfo );

   if ( !ok ) {
      sProcessInfo.hProcess = 0;
      return sProcessInfo.hProcess;
   }

   return sProcessInfo.hProcess;
}

HANDLE ExecuteProcessInvisible( const string & CommandLine, const string & WorkDir )
{
   STARTUPINFOA sStartInfo;
   ZeroMemory( &sStartInfo, sizeof(STARTUPINFO) );
   sStartInfo.cb = sizeof(STARTUPINFO);
   sStartInfo.wShowWindow = SW_SHOWDEFAULT;
   sStartInfo.dwFlags = STARTF_USESHOWWINDOW;

   PROCESS_INFORMATION sProcessInfo;
   ZeroMemory( &sProcessInfo, sizeof(PROCESS_INFORMATION) );

   BOOL ok = CreateProcessA( NULL, (char*)CommandLine.c_str(),
                           NULL, NULL, true,
                           NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW, NULL, WorkDir.c_str() , &sStartInfo, &sProcessInfo );

   if ( !ok ) {
      sProcessInfo.hProcess = 0;
      return sProcessInfo.hProcess;
   }

   return sProcessInfo.hProcess;
}

HANDLE ExecuteProcessWait( const string & CommandLine, const string & WorkDir )
{
   STARTUPINFOA sStartInfo;
   ZeroMemory( &sStartInfo, sizeof(STARTUPINFO) );
   sStartInfo.cb = sizeof(STARTUPINFO);
   sStartInfo.wShowWindow = SW_SHOWDEFAULT;
   sStartInfo.dwFlags = STARTF_USESHOWWINDOW;

   PROCESS_INFORMATION sProcessInfo;
   ZeroMemory( &sProcessInfo, sizeof(PROCESS_INFORMATION) );

   BOOL ok = CreateProcessA( NULL, (char*)CommandLine.c_str(),
                           NULL, NULL, true,
                           NORMAL_PRIORITY_CLASS, NULL, WorkDir.c_str() , &sStartInfo, &sProcessInfo );

   if ( !ok ) {
      sProcessInfo.hProcess = 0;
      return sProcessInfo.hProcess;
   }

   unsigned long ExitCode=0;
   while(GetExitCodeProcess(sProcessInfo.hProcess , &ExitCode)&&ExitCode== STILL_ACTIVE)
   {
          Sleep((unsigned long)50);
   }

   return sProcessInfo.hProcess;
}
