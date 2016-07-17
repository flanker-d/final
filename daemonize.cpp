#include "daemonize.h"

daemonize::daemonize()
{
  pid_t pid = fork();
  if (pid < 0)
  {
    std::cout << "Failed to fork:" << strerror(errno) << std::endl;
    return;
  }
  else if (pid > 0)
  {
    std::cout << "Daemon process with pid" << pid << "created." << std::endl;
    exit(0);
  }
  else
  {
    /* child (daemon) process is here */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    pid_t sid = setsid();
    if (sid < 0)
    {
      std::cout << "Failed to set the session id: " << strerror(errno) << std::endl;
      return;
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0)
    {
      std::cout << "Failed to change the current working directory: " << strerror(errno) << std::endl;
      return;
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }
}
