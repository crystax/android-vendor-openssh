#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

#include "pathnames.h"

#undef _CONFIGURED_SSHDIR
#undef _CONFIGURED_BINDIR
#undef _CONFIGURED_LIBEXECDIR
#undef _CONFIGURED_PATH_SSH_PIDDIR
#undef _CONFIGURED_PATH_PRIVSEP_CHROOT_DIR

#ifndef _CONFIGURED_ROOTDIR
#define _CONFIGURED_ROOTDIR "/"
#endif

#ifndef _CONFIGURED_SSHDIR
#define _CONFIGURED_SSHDIR "/etc"
#endif

#ifndef _CONFIGURED_BINDIR
#define _CONFIGURED_BINDIR "/bin"
#endif

#ifndef _CONFIGURED_LIBEXECDIR
#define _CONFIGURED_LIBEXECDIR "/libexec"
#endif

#ifndef _CONFIGURED_PATH_SSH_PIDDIR
#define _CONFIGURED_PATH_SSH_PIDDIR "/run"
#endif

#ifndef _CONFIGURED_PATH_PRIVSEP_CHROOT_DIR
#define _CONFIGURED_PATH_PRIVSEP_CHROOT_DIR "/var/empty"
#endif

#define OPENSSH_JOIN(a, b) OPENSSH_JOIN2(a, b)
#define OPENSSH_JOIN2(a, b) a ## b

#define OPENSSH_DEFINE_PATH(funcname, rootdir, subpath) \
    static char OPENSSH_JOIN(openssh_path_buf_, funcname)[PATH_MAX] = {0}; \
    static pthread_mutex_t OPENSSH_JOIN(openssh_path_mtx_, funcname) = PTHREAD_MUTEX_INITIALIZER; \
    char *OPENSSH_JOIN(openssh_path_, funcname)() { \
        if (strcmp(rootdir, "/") == 0 && subpath[0] == '/') \
            return subpath; \
        if (pthread_mutex_lock(&OPENSSH_JOIN(openssh_path_mtx_, funcname)) != 0) { \
            fprintf(stderr, "*** FATAL: Can't lock mutex for openssh_path_%s\n", #funcname); \
            abort(); \
        } \
        if (OPENSSH_JOIN(openssh_path_buf_, funcname)[0] == '\0') { \
            int rc = snprintf(OPENSSH_JOIN(openssh_path_buf_, funcname), \
                        sizeof(OPENSSH_JOIN(openssh_path_buf_, funcname)), \
                        "%s/%s", rootdir, subpath); \
            if (rc < 0 || (size_t)rc >= sizeof(OPENSSH_JOIN(openssh_path_buf_, funcname))) { \
                fprintf(stderr, "*** FATAL: Path '%s' is too long!\n", rootdir); \
                abort(); \
            } \
        } \
        if (pthread_mutex_unlock(&OPENSSH_JOIN(openssh_path_mtx_, funcname)) != 0) { \
            fprintf(stderr, "*** FATAL: Can't unlock mutex for openssh_path_%s\n", #funcname); \
            abort(); \
        } \
        return OPENSSH_JOIN(openssh_path_buf_, funcname); \
    }

#define OPENSSH_DEFINE_ETCFILE(fname, file) \
    OPENSSH_DEFINE_PATH(fname, openssh_path_etcdir(), "/" file)

#define OPENSSH_DEFINE_BINFILE(fname, file) \
    OPENSSH_DEFINE_PATH(fname, openssh_path_bindir(), "/" file)

#define OPENSSH_DEFINE_LIBEXECFILE(fname, file) \
    OPENSSH_DEFINE_PATH(fname, openssh_path_libexecdir(), "/" file)

static char rootdir_buf[PATH_MAX] = {0};
static pthread_mutex_t rootdir_mtx = PTHREAD_MUTEX_INITIALIZER;

void openssh_path_set_rootdir(const char *path)
{
    int rc;

    if (pthread_mutex_lock(&rootdir_mtx) != 0) {
        fprintf(stderr, "*** FATAL: Can't lock mutex for openssh_path_rootdir\n");
        abort();
    }

    rc = snprintf(rootdir_buf, sizeof(rootdir_buf), "%s", path);
    if (rc < 0 || (size_t)rc >= sizeof(rootdir_buf)) {
        fprintf(stderr, "*** FATAL: Provided path '%s' is too long!\n", path);
        abort();
    }

    if (pthread_mutex_unlock(&rootdir_mtx) != 0) {
        fprintf(stderr, "*** FATAL: Can't unlock mutex for openssh_path_rootdir\n");
        abort();
    }
}

char *openssh_path_rootdir()
{
    int rc;

    if (pthread_mutex_lock(&rootdir_mtx) != 0) {
        fprintf(stderr, "*** FATAL: Can't lock mutex for openssh_path_rootdir\n");
        abort();
    }

    if (rootdir_buf[0] == '\0') {
        rc = snprintf(rootdir_buf, sizeof(rootdir_buf), "%s", _CONFIGURED_ROOTDIR);
        if (rc < 0 || (size_t)rc >= sizeof(rootdir_buf)) {
            fprintf(stderr, "*** FATAL: Built-in root path '%s' is too long!\n", _CONFIGURED_ROOTDIR);
            abort();
        }
    }

    if (pthread_mutex_unlock(&rootdir_mtx) != 0) {
        fprintf(stderr, "*** FATAL: Can't unlock mutex for openssh_path_rootdir\n");
        abort();
    }

    return rootdir_buf;
}

OPENSSH_DEFINE_PATH(bindir,              openssh_path_rootdir(), _CONFIGURED_BINDIR)
OPENSSH_DEFINE_PATH(etcdir,              openssh_path_rootdir(), _CONFIGURED_SSHDIR)
OPENSSH_DEFINE_PATH(libexecdir,          openssh_path_rootdir(), _CONFIGURED_LIBEXECDIR)
OPENSSH_DEFINE_PATH(privsep_chroot_dir,  openssh_path_rootdir(), _CONFIGURED_PATH_PRIVSEP_CHROOT_DIR)
OPENSSH_DEFINE_PATH(piddir,              openssh_path_rootdir(), _CONFIGURED_PATH_SSH_PIDDIR)

OPENSSH_DEFINE_PATH(ssh_daemon_pid_file, openssh_path_piddir(), "/sshd.pid")

OPENSSH_DEFINE_ETCFILE(system_hostfile,       "ssh_known_hosts")
OPENSSH_DEFINE_ETCFILE(system_hostfile2,      "ssh_known_hosts2")
OPENSSH_DEFINE_ETCFILE(server_config_file,    "sshd_config")
OPENSSH_DEFINE_ETCFILE(host_config_file,      "ssh_config")
OPENSSH_DEFINE_ETCFILE(host_key_file,         "ssh_host_key")
OPENSSH_DEFINE_ETCFILE(host_dsa_key_file,     "ssh_host_dsa_key")
OPENSSH_DEFINE_ETCFILE(host_ecdsa_key_file,   "ssh_host_ecdsa_key")
OPENSSH_DEFINE_ETCFILE(host_ed25519_key_file, "ssh_host_ed25519_key")
OPENSSH_DEFINE_ETCFILE(host_rsa_key_file,     "ssh_host_rsa_key")
OPENSSH_DEFINE_ETCFILE(dh_moduli,             "moduli")
OPENSSH_DEFINE_ETCFILE(dh_primes,             "primes")
OPENSSH_DEFINE_ETCFILE(system_rc,             "sshrc")
OPENSSH_DEFINE_ETCFILE(hosts_equiv,           "shosts.equiv")

OPENSSH_DEFINE_BINFILE(ssh_program, "ssh")

OPENSSH_DEFINE_LIBEXECFILE(key_sign,      "ssh-keysign")
OPENSSH_DEFINE_LIBEXECFILE(pkcs11_helper, "ssh-pkcs11-helper")
OPENSSH_DEFINE_LIBEXECFILE(sftp_server,   "sftp-server")
