/* $OpenBSD: pathnames.h,v 1.28 2018/02/23 15:58:37 markus Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#ifdef __cplusplus
extern "C" {
#endif

void openssh_path_set_rootdir(const char *path);

#define ETCDIR				"/etc"

#ifndef SSHDIR
#define SSHDIR				ETCDIR "/ssh"
#endif

#undef SSHDIR
#define SSHDIR openssh_path_etcdir()
char *openssh_path_etcdir();

#ifndef _PATH_SSH_PIDDIR
#define _PATH_SSH_PIDDIR		"/var/run"
#endif

#undef _PATH_SSH_PIDDIR
#define _PATH_SSH_PIDDIR openssh_path_piddir()
char *openssh_path_piddir();

/*
 * System-wide file containing host keys of known hosts.  This file should be
 * world-readable.
 */
#define _PATH_SSH_SYSTEM_HOSTFILE	SSHDIR "/ssh_known_hosts"
/* backward compat for protocol 2 */
#define _PATH_SSH_SYSTEM_HOSTFILE2	SSHDIR "/ssh_known_hosts2"

#undef _PATH_SSH_SYSTEM_HOSTFILE
#undef _PATH_SSH_SYSTEM_HOSTFILE2
#define _PATH_SSH_SYSTEM_HOSTFILE  openssh_path_system_hostfile()
#define _PATH_SSH_SYSTEM_HOSTFILE2 openssh_path_system_hostfile2()
char *openssh_path_system_hostfile();
char *openssh_path_system_hostfile2();

/*
 * Of these, ssh_host_key must be readable only by root, whereas ssh_config
 * should be world-readable.
 */
#define _PATH_SERVER_CONFIG_FILE	SSHDIR "/sshd_config"
#undef  _PATH_SERVER_CONFIG_FILE
#define _PATH_SERVER_CONFIG_FILE openssh_path_server_config_file()
char *openssh_path_server_config_file();

#define _PATH_HOST_CONFIG_FILE		SSHDIR "/ssh_config"
#undef  _PATH_HOST_CONFIG_FILE
#define _PATH_HOST_CONFIG_FILE openssh_path_host_config_file()
char *openssh_path_host_config_file();

#define _PATH_HOST_KEY_FILE		SSHDIR "/ssh_host_key"
#undef  _PATH_HOST_KEY_FILE
#define _PATH_HOST_KEY_FILE openssh_path_host_key_file()
char *openssh_path_host_key_file();

#define _PATH_HOST_DSA_KEY_FILE		SSHDIR "/ssh_host_dsa_key"
#undef  _PATH_HOST_DSA_KEY_FILE
#define _PATH_HOST_DSA_KEY_FILE openssh_path_host_dsa_key_file()
char *openssh_path_host_dsa_key_file();

#define _PATH_HOST_ECDSA_KEY_FILE	SSHDIR "/ssh_host_ecdsa_key"
#undef  _PATH_HOST_ECDSA_KEY_FILE
#define _PATH_HOST_ECDSA_KEY_FILE openssh_path_host_ecdsa_key_file()
char *openssh_path_host_ecdsa_key_file();

#define _PATH_HOST_ED25519_KEY_FILE	SSHDIR "/ssh_host_ed25519_key"
#undef  _PATH_HOST_ED25519_KEY_FILE
#define _PATH_HOST_ED25519_KEY_FILE openssh_path_host_ed25519_key_file()
char *openssh_path_host_ed25519_key_file();

#define _PATH_HOST_XMSS_KEY_FILE	SSHDIR "/ssh_host_xmss_key"
#undef  _PATH_HOST_XMSS_KEY_FILE
#define _PATH_HOST_XMSS_KEY_FILE openssh_path_host_xmss_key_file()
char *openssh_path_host_xmss_key_file();

#define _PATH_HOST_RSA_KEY_FILE		SSHDIR "/ssh_host_rsa_key"
#undef  _PATH_HOST_RSA_KEY_FILE
#define _PATH_HOST_RSA_KEY_FILE openssh_path_host_rsa_key_file()
char *openssh_path_host_rsa_key_file();

#define _PATH_DH_MODULI			SSHDIR "/moduli"
#undef  _PATH_DH_MODULI
#define _PATH_DH_MODULI openssh_path_dh_moduli()
char *openssh_path_dh_moduli();

/* Backwards compatibility */
#define _PATH_DH_PRIMES			SSHDIR "/primes"
#undef  _PATH_DH_PRIMES
#define _PATH_DH_PRIMES openssh_path_dh_primes()
char *openssh_path_dh_primes();

#ifndef _PATH_SSH_PROGRAM
#define _PATH_SSH_PROGRAM		"/usr/bin/ssh"
#endif

#undef  _PATH_SSH_PROGRAM
#define _PATH_SSH_PROGRAM openssh_path_ssh_program()
char *openssh_path_ssh_program();

/*
 * The process id of the daemon listening for connections is saved here to
 * make it easier to kill the correct daemon when necessary.
 */
#define _PATH_SSH_DAEMON_PID_FILE	_PATH_SSH_PIDDIR "/sshd.pid"
#undef  _PATH_SSH_DAEMON_PID_FILE
#define _PATH_SSH_DAEMON_PID_FILE openssh_path_ssh_daemon_pid_file()
char *openssh_path_ssh_daemon_pid_file();

/*
 * The directory in user's home directory in which the files reside. The
 * directory should be world-readable (though not all files are).
 */
#define _PATH_SSH_USER_DIR		".ssh"

/*
 * Per-user file containing host keys of known hosts.  This file need not be
 * readable by anyone except the user him/herself, though this does not
 * contain anything particularly secret.
 */
#define _PATH_SSH_USER_HOSTFILE		"~/" _PATH_SSH_USER_DIR "/known_hosts"
/* backward compat for protocol 2 */
#define _PATH_SSH_USER_HOSTFILE2	"~/" _PATH_SSH_USER_DIR "/known_hosts2"

/*
 * Name of the default file containing client-side authentication key. This
 * file should only be readable by the user him/herself.
 */
#define _PATH_SSH_CLIENT_ID_DSA		_PATH_SSH_USER_DIR "/id_dsa"
#define _PATH_SSH_CLIENT_ID_ECDSA	_PATH_SSH_USER_DIR "/id_ecdsa"
#define _PATH_SSH_CLIENT_ID_RSA		_PATH_SSH_USER_DIR "/id_rsa"
#define _PATH_SSH_CLIENT_ID_ED25519	_PATH_SSH_USER_DIR "/id_ed25519"
#define _PATH_SSH_CLIENT_ID_XMSS	_PATH_SSH_USER_DIR "/id_xmss"

/*
 * Configuration file in user's home directory.  This file need not be
 * readable by anyone but the user him/herself, but does not contain anything
 * particularly secret.  If the user's home directory resides on an NFS
 * volume where root is mapped to nobody, this may need to be world-readable.
 */
#define _PATH_SSH_USER_CONFFILE		_PATH_SSH_USER_DIR "/config"

/*
 * File containing a list of those rsa keys that permit logging in as this
 * user.  This file need not be readable by anyone but the user him/herself,
 * but does not contain anything particularly secret.  If the user's home
 * directory resides on an NFS volume where root is mapped to nobody, this
 * may need to be world-readable.  (This file is read by the daemon which is
 * running as root.)
 */
#define _PATH_SSH_USER_PERMITTED_KEYS	_PATH_SSH_USER_DIR "/authorized_keys"

/* backward compat for protocol v2 */
#define _PATH_SSH_USER_PERMITTED_KEYS2	_PATH_SSH_USER_DIR "/authorized_keys2"

/*
 * Per-user and system-wide ssh "rc" files.  These files are executed with
 * /bin/sh before starting the shell or command if they exist.  They will be
 * passed "proto cookie" as arguments if X11 forwarding with spoofing is in
 * use.  xauth will be run if neither of these exists.
 */
#define _PATH_SSH_USER_RC		_PATH_SSH_USER_DIR "/rc"
#define _PATH_SSH_SYSTEM_RC		SSHDIR "/sshrc"
#undef  _PATH_SSH_SYSTEM_RC
#define _PATH_SSH_SYSTEM_RC openssh_path_system_rc()
char *openssh_path_system_rc();

/*
 * Ssh-only version of /etc/hosts.equiv.  Additionally, the daemon may use
 * ~/.rhosts and /etc/hosts.equiv if rhosts authentication is enabled.
 */
#define _PATH_SSH_HOSTS_EQUIV		SSHDIR "/shosts.equiv"
#undef  _PATH_SSH_HOSTS_EQUIV
#define _PATH_SSH_HOSTS_EQUIV openssh_path_hosts_equiv()
char *openssh_path_hosts_equiv();

#define _PATH_RHOSTS_EQUIV		"/etc/hosts.equiv"

/*
 * Default location of askpass
 */
#ifndef _PATH_SSH_ASKPASS_DEFAULT
#define _PATH_SSH_ASKPASS_DEFAULT	"/usr/X11R6/bin/ssh-askpass"
#endif

/* Location of ssh-keysign for hostbased authentication */
#ifndef _PATH_SSH_KEY_SIGN
#define _PATH_SSH_KEY_SIGN		"/usr/libexec/ssh-keysign"
#endif

#undef  _PATH_SSH_KEY_SIGN
#define _PATH_SSH_KEY_SIGN openssh_path_key_sign()
char *openssh_path_key_sign();

/* Location of ssh-pkcs11-helper to support keys in tokens */
#ifndef _PATH_SSH_PKCS11_HELPER
#define _PATH_SSH_PKCS11_HELPER		"/usr/libexec/ssh-pkcs11-helper"
#endif

#undef  _PATH_SSH_PKCS11_HELPER
#define _PATH_SSH_PKCS11_HELPER openssh_path_pkcs11_helper()
char *openssh_path_pkcs11_helper();

/* xauth for X11 forwarding */
#ifndef _PATH_XAUTH
#define _PATH_XAUTH			"/usr/X11R6/bin/xauth"
#endif

/* UNIX domain socket for X11 server; displaynum will replace %u */
#ifndef _PATH_UNIX_X
#define _PATH_UNIX_X "/tmp/.X11-unix/X%u"
#endif

/* for scp */
#ifndef _PATH_CP
#define _PATH_CP			"cp"
#endif

/* for sftp */
#ifndef _PATH_SFTP_SERVER
#define _PATH_SFTP_SERVER		"/usr/libexec/sftp-server"
#endif

#undef  _PATH_SFTP_SERVER
#define _PATH_SFTP_SERVER openssh_path_sftp_server()
char *openssh_path_sftp_server();

/* chroot directory for unprivileged user when UsePrivilegeSeparation=yes */
#ifndef _PATH_PRIVSEP_CHROOT_DIR
#define _PATH_PRIVSEP_CHROOT_DIR	"/var/empty"
#endif

#undef  _PATH_PRIVSEP_CHROOT_DIR
#define _PATH_PRIVSEP_CHROOT_DIR openssh_path_privsep_chroot_dir()
char *openssh_path_privsep_chroot_dir();

/* for passwd change */
#ifndef _PATH_PASSWD_PROG
#define _PATH_PASSWD_PROG             "/usr/bin/passwd"
#endif

#ifndef _PATH_LS
#define _PATH_LS			"ls"
#endif

/* Askpass program define */
#ifndef ASKPASS_PROGRAM
#define ASKPASS_PROGRAM         "/usr/lib/ssh/ssh-askpass"
#endif /* ASKPASS_PROGRAM */

#ifdef __cplusplus
} // extern "C"
#endif
