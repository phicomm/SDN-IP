/* Copyright (C) 2013 IP Infusion, Inc. All Rights Reserved.  */

#ifndef _BGPSDN_CLI_H
#define _BGPSDN_CLI_H

#include "modbmap.h"
#include "cli_mode_types.h"
#include "cfg_data_types.h"

/* CLI macro.  Macro defines a CLI structure and a CLI function.  C99
   C preprocessor variadic macros is used to define arbitrary number
   of help string definition.  */

/* Perl script is used for extracting CLI and ALI macro from source
   code.  In that case EXTRACT_CLI should be defined to prevent macro
   expansion.  */

#ifndef EXTRACT_CLI

#ifdef HAVE_ISO_MACRO_VARARGS
#define CLI(func_name, cli_name, cmd_str, ...)                          \
                                                                        \
/* Function prototype.  */                                              \
int func_name (struct cli *, int, char**);                              \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {__VA_ARGS__, NULL};                        \
                                                                        \
/* Define CLI structure.  */                                            \
struct cli_element cli_name =                                           \
{                                                                       \
  /* Command line string.  */                                           \
  cmd_str,                                                              \
                                                                        \
   /* Function pointer.  */                                             \
  func_name,                                                            \
                                                                        \
  /* Help string is defined as an array.  Last must be NULL.  */        \
  cli_name ## _help                                                     \
};                                                                      \
                                                                        \
/* Start function body at here.  */                                     \
int func_name (struct cli *cli, int argc, char** argv)

/* ALIAS to CLI macro.  Define CLI structure only.  There is no
   function body.  */
#define ALI(func_name, cli_name, cmd_str, ...)                          \
                                                                        \
extern int func_name (struct cli *cli, int argc, char** argv);          \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {__VA_ARGS__, NULL};                        \
                                                                        \
struct cli_element cli_name =                                           \
{                                                                       \
  cmd_str,                                                              \
  func_name,                                                            \
  cli_name ## _help                                                     \
}

/* IMI/IMISH ALI generated by cli.pl for IMI and IMIsh.  */
#define IMI_ALI(func_name, cli_name, cmd_str, ...)                      \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {__VA_ARGS__, NULL};                        \
                                                                        \
struct cli_element cli_name =                                           \
{                                                                       \
  cmd_str,                                                              \
  func_name,                                                            \
  cli_name ## _help                                                     \
}

#else

#define CLI(func_name, cli_name, cmd_str, ARGS...)                      \
                                                                        \
/* Function prototype.  */                                              \
int func_name (struct cli *, int, char**);                              \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {##ARGS, NULL};                             \
                                                                        \
/* Define CLI structure.  */                                            \
struct cli_element cli_name =                                           \
{                                                                       \
  /* Command line string.  */                                           \
  cmd_str,                                                              \
                                                                        \
   /* Function pointer.  */                                             \
  func_name,                                                            \
                                                                        \
  /* Help string is defined as an array.  Last must be NULL.  */        \
  cli_name ## _help                                                     \
};                                                                      \
                                                                        \
/* Start function body at here.  */                                     \
int func_name (struct cli *cli, int argc, char** argv)

/* ALIAS to CLI macro.  Define CLI structure only.  There is no
   function body.  */
#define ALI(func_name, cli_name, cmd_str, ARGS...)                      \
                                                                        \
extern int func_name (struct cli *cli, int argc, char** argv);          \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {##ARGS, NULL};                             \
                                                                        \
struct cli_element cli_name =                                           \
{                                                                       \
  cmd_str,                                                              \
  func_name,                                                            \
  cli_name ## _help                                                     \
}

/* IMI/IMIsh ALI generated by cli.pl for IMI and IMIsh.  */
#define IMI_ALI(func_name, cli_name, cmd_str, ARGS...)                  \
                                                                        \
/* Help string array.  */                                               \
char *cli_name ## _help[] = {##ARGS, NULL};                             \
                                                                        \
struct cli_element cli_name =                                           \
{                                                                       \
  cmd_str,                                                              \
  func_name,                                                            \
  cli_name ## _help                                                     \
}

#endif /* HAVE_ISO_MACRO_VARARGS. */
#endif /* EXTRACT_CLI */

/* CLI output function.  We can switch over CLI output function
   defining cli->out_func.  */

typedef int (*CLI_OUT_FUNC) (void *, char *, ...);

/* CLI output function macro.  Instead of defining a function, user
   can specify CLI output function dynamically.  */
#ifdef HAVE_ISO_MACRO_VARARGS
#define cli_out(cli, ...)                                                     \
        (*(cli)->out_func)((cli)->out_val, __VA_ARGS__)
#else
#define cli_out(cli, ARGS...)                                                 \
        (*(cli)->out_func)((cli)->out_val, ##ARGS)
#endif /* HAVE_ISO_MACRO_VARARGS. */

/* CLI parsing tree.  This structure has all of CLI commands and run
   time variables such as mode and privilege.  Mode and privilege
   level will be passed to cli_parse() function then set to this
   structure.  */

struct cli_tree
{
  /* Current mode.  */
  int mode;

  /* Privilege level.  */
  u_char privilege;

  /* Vector of modes.  */
  vector modes;

  /* Vector of configuration output function.  */
  vector config_write;

  /* Node to be executed.  */
  struct cli_node *exec_node;

  /* Possibly matched cel.  Function internal use only.  */
  vector v;

  /* Traverse nodes. */
  vector t;

  /* Expand is needed.  Used by describe function.  */
  int expand_node;

  /* Show node match result.  */
  int show_node;

  /* Used to suppress the default paging of a nested show command. */
  bool_t nested_show;

  /* Parsed argc and argv.  */
  int argc;
#define CLI_ARGC_MAX               128
#define CLI_ARGV_MAX_LEN           256
  char *argv[CLI_ARGC_MAX];

  /* For Output Modifier.  */
  struct cli_node *modifier_node;
  int argc_modifier;
  char *argv_modifier[CLI_ARGC_MAX];
  char *rem;

  /* Parse failed character pointer to show invalid input.  */
  char *invalid;

  /* To show pipe pointer.  */
  char *pipe;

  /* Advanced mode.  */
  int advanced;
};

/* Argument to cli functions.  */
struct cli
{
  /* CLI element.  */
  struct cli_element *cel;

  /* User input string.  */
  char *str;

  /* Output function to be used by cli_out().  */
  CLI_OUT_FUNC out_func;

  /* Output function's first argument.  */
  void *out_val;

  /* Arbitrary information for line.  */
  void *line;

  /* Auth required.  */
  int auth;

  /* Input source.  */
  int source;
#define CLI_SOURCE_USER                 0
#define CLI_SOURCE_FILE                 1

  /* For "line". */
  int line_type;
  int min;
  int max;

  /* Real CLI.  */
  void *index;
  void *index_sub;
  int mode;

  /* Current CLI status.  */
  enum {
    CLI_NORMAL,
    CLI_CLOSE,
    CLI_MORE,
    CLI_CONTINUE,
    CLI_MORE_CONTINUE,
    CLI_WAIT
  } status;

  /* Flags. */
  u_char flags;
#define CLI_FROM_PVR    (1 << 0)

  void *self;
  u_char privilege;
  struct cli_tree *ctree;

  /* Global variable.  */
  struct lib_globals *zg;
  struct ipi_vr *vr;

  /* Terminal length.  */
  int lines;

  /* Call back function.  */
  int (*callback) (struct cli *);
  int (*cleanup) (struct cli *);
  s_int32_t (*show_func) (struct cli *);
  int type;
  u_int32_t count;
  void *current;
  void *arg;
  afi_t afi;
  safi_t safi;

  /* Vector used by IMI to encode a single CLI command string.
   */
  cfg_vect_t *cv;
};

/* Configuration output function.  */

typedef int (*CLI_CONFIG_FUNC) (struct cli *cli);

/* CLI element.  */
struct cli_element
{
  /* Command line string.  */
  char *str;

  /* Function to execute this command.  */
  int (*func) (struct cli *, int, char **);

  /* Help strings array. */
  char **help;

  /* Unique key. */
  int key;

  /* Flags of the commands.  */
  u_int16_t flags;

  /* When CLI_FLAG_HIDDEN is defined, the command isn't used for
     completion.  */
#define CLI_FLAG_HIDDEN            (1 << 0)

  /* When CLI_FLAG_MODIFIER is define, output modifier '|' can be used
     for the command.  Usually the flag is set to show commands.  */
#define CLI_FLAG_MODIFIER          (1 << 1)

  /* This is only used by struct cli_node.  When the node is "show" or
     "*s=show" this flag should be set.  */
#define CLI_FLAG_SHOW              (1 << 2)

  /* This is only used by struct cli_node.  When the node is in
     parenthesis this flag is set.  */
#define CLI_FLAG_PAREN             (1 << 3)

  /* This node is in brace.  */
#define CLI_FLAG_TRAVERSE          (1 << 4)

  /* This node is recursive.  */
#define CLI_FLAG_RECURSIVE         (1 << 5)

  /* Execute CLI function before send it to IMI.  */
#define CLI_FLAG_LOCAL_FIRST       (1 << 6)

  /* This enforce not apply the pager to the output.  */
#define CLI_FLAG_NO_PAGER          (1 << 7)

  /* This flag is used for interface name match.  */
#define CLI_FLAG_IFNAME            (1 << 8)

  /* This is only used by WMI (Web Management Interface). */
#define CLI_FLAG_WMI               (1 << 9)

  /* Set if ignore PM command error is required at the IMI level. */
#define CLI_FLAG_IGN_PM_DOWN_ERR   (1 << 10)

  /* Send this command to all on the list, regardless of failures returned by some. */
#define CLI_FLAG_MCAST   (1 << 11)

#define CLI_PLUS_SIGN_FORBIDDEN   (1 << 12)

  /* Protocol module to which this command belongs. */
  modbmap_t module;

  /* This is the conifguration data type the command will
     deliver to the IMI module. For use only by IMI module.
   */
  /*  cfgDataType_e data_type; */
   u_int16_t data_type;

  /* This is the mode which the CLI will switch into, if the
     mode change command completes successfully.
   */
  u_int16_t     new_mode;
};

/* CLI tree node.  */
struct cli_node
{
  /* CLI token types.  */
  enum cli_token
    {
      cli_token_paren_open,
      cli_token_paren_close,
      cli_token_cbrace_open,
      cli_token_cbrace_close,
      cli_token_brace_open,
      cli_token_brace_close,
      cli_token_ifname_open,
      cli_token_ifname_close,
      cli_token_separator,
      cli_token_pipe,
      cli_token_redirect,
      cli_token_dot,
      cli_token_question,
      cli_token_range,
      cli_token_keyword,
      cli_token_alias,
      cli_token_line,
      cli_token_word,
      cli_token_ipv4,
      cli_token_ipv4_prefix,
      cli_token_ipv6,
      cli_token_ipv6_prefix,
      cli_token_time,
      cli_token_community,
      cli_token_mac_address,
      cli_token_ifname,
      cli_token_unknown
    } type;

  /* String to be matched.  */
  char *str;

  /* Help string.  */
  char *help;

  /* Max and min.  */
  u_int32_t max;
  u_int32_t min;

  /* Pointer to CLI element.  */
  struct cli_element *cel;

  /* Vector of next nodes.  */
  vector keywords;

  /* Privilege node.  */
  u_char privilege;

  /* Same as cli_element's flags.  */
  u_int16_t flags;

  /* Reference count.  */
  u_int32_t refcnt;
};

/* Return value.  */
#define CLI_SUCCESS           0
#define CLI_ERROR             1
#define CLI_AUTH_REQUIRED     2
#define CLI_EOL               3

/* Privilege level.  */
#define PRIVILEGE_MIN         1
#define PRIVILEGE_VR_MAX     15
#define PRIVILEGE_PVR_MAX    16

#define PRIVILEGE_NORMAL        PRIVILEGE_MIN
#ifdef HAVE_VR
#define PRIVILEGE_MAX           (PRIVILEGE_PVR_MAX)
#define PRIVILEGE_ENABLE(V)                                                   \
    ((V)->id == 0 ? PRIVILEGE_PVR_MAX : PRIVILEGE_VR_MAX)
#else /* HAVE_VR */
#define PRIVILEGE_MAX           (PRIVILEGE_VR_MAX)
#define PRIVILEGE_ENABLE(V)     (PRIVILEGE_VR_MAX)
#endif /* HAVE_VR */

/* Max length of each token.  */
#define MAX_TOKEN_LENGTH   256

#define MODULE_ID2MODE(MODULE_ID)                                             \
    ((MODULE_ID) == IPI_PROTO_BGP    ? BGP_MODE    : PAL_FALSE)               \

/* CLI parser result codes.  */
#define CLI_PARSE_SUCCESS             0
#define CLI_PARSE_INCOMPLETE          1
#define CLI_PARSE_INCOMPLETE_PIPE     2
#define CLI_PARSE_EMPTY_LINE          3
#define CLI_PARSE_AMBIGUOUS           4
#define CLI_PARSE_NO_MATCH            5
#define CLI_PARSE_NO_MODE             6
#define CLI_PARSE_ARGV_TOO_LONG       7

/* Common descriptions. */
#define CLI_IFNAME_STR  "Interface name"
#define CLI_SHOW_STR "Show running system information"
#define CLI_STATS_STR "Statistics"
#define CLI_SHOW_MEMORY_STR  "Memory information"
#define CLI_SHOW_BRIDGE_STR  "Bridge information"
#define CLI_NO_STR "Negate a command or set its defaults"
#define CLI_WRITE_STR "Write running configuration to memory, file or terminal"
#define CLI_CLEAR_STR "Reset functions"
#define CLI_IP_STR "Internet Protocol (IP)"
#define CLI_IPV6_STR "Internet Protocol version 6 (IPv6)"
#define CLI_BGP_STR "Border Gateway Protocol (BGP)"
/*MAC-based auth Enhancement*/
#define CLI_NEIGHBOR_STR "Specify a neighbor router"
#define CLI_AF_STR "Address family"
#define CLI_AFM_STR "Address family modifier"
#define CLI_DEBUG_STR "Debugging functions (see also 'undebug')"
#define CLI_UNDEBUG_STR "Disable debugging functions (see also 'debug')"
#define CLI_UNDEBUG_ALL_STR "Turn off all Debugging"
#define CLI_ROUTER_STR "Enable a routing process"
#define CLI_AS_STR "AS number"
#define CLI_MATCH_STR "Match values from routing table"
#define CLI_SET_STR "Set values in destination routing protocol"
#define CLI_OUT_STR "Filter outgoing routing updates"
#define CLI_IN_STR  "Filter incoming routing updates"
#define CLI_V4NOTATION_STR "specify by IPv4 address notation(e.g. 0.0.0.0)"
#define CLI_INTERFACE_STR "Interface information"
#define CLI_SECONDS_STR "<1-65535> Seconds"
#define CLI_ROUTE_STR "Routing Table"
#define CLI_PREFIX_LIST_STR "Build a prefix list"
#define CLI_CLEAR_PREFIX_LIST_STR "Clear a prefix list"
#define CLI_VR_STR "Virtual-router configuration"
#define CLI_VR_NAME_STR "Virtual-router name" " (max " VAR_SUPERSTR (LIB_VR_MAX_NAMELEN) " characters)"
#define CLI_VR_ID_STR "Virtual Router ID"
#define CLI_VR_EXPORT_STR "Export routes between virtual-routers"
#define CLI_ACCESS_GROUP_STR "Access Group "
#define CLI_KEYSTRING_STR "Set key string"
#define CLI_KEYCHAIN_ACCEPT_LIFETIME_STR "Set accept lifetime of the key"
#define CLI_KEYCHAIN_SEND_LIFETIME_STR "Set send lifetime of the key"
#define CLI_ROUTEMAP_STR "Create route-map or enter route-map command mode"
#define CLI_ACCESS_STR "Add an access list entry"
#define CLI_ACCESS_GRP_STR "Add an access group entry"
#define CLI_ACCESS_LIST_NAME_STR "Access-list name"
#define CLI_ACCESS_BGPSDN_STR "BGP-SDN access-list name"
#define CLI_ACCESS6_BGPSDN_STR "IPv6 BGP-SDN access-list name"
#define CLI_ACCESS_PERMIT_STR "Specify packets to forward"
#define CLI_ACCESS_DENY_STR "Specify packets to reject"
#define CLI_PREFIX_LIST_NAME_STR "Name of a prefix list"
#define CLI_PREFIX_NETWORK_STR "IP prefix <network>/<length>, e.g., 35.0.0.0/8"
#define CLI_PREFIX6_NETWORK_STR "IPv6 prefix <network>/<length>, e.g., 3ffe::/16"
#define CLI_PREFIX_LENGTH_MIN "Minimum prefix length"
#define CLI_PREFIX_LENGTH_MAX "Maximum prefix length"
#define CLI_PREFIX_LENGTH_MIN_MATCH "Minimum prefix length to be matched"
#define CLI_PREFIX_LENGTH_MAX_MATCH "Maximum prefix length to be matched"
#define CLI_PREFIX_SEQ_STR "Sequence number of an entry"
#define CLI_PREFIX_SEQNUM_STR "Sequence number"

/*
 * The following macros are used when
 * the CLI used for deleting a entry is provided with only mandatory parameters.
 */
#define CLI_MIN_PARAMS_ENTRY_DELETE             0
#define CLI_MAX_PARAMS_ENTRY_DELETE             1
  
#ifdef HAVE_IPV6
#define NEIGHBOR_CMD       "neighbor (A.B.C.D|X:X::X:X) "
#define NO_NEIGHBOR_CMD    "no neighbor (A.B.C.D|X:X::X:X) "
#define NEIGHBOR_ADDR_STR  "IP address","IPv6 address"
#define NEIGHBOR_CMD2      "neighbor (A.B.C.D|X:X::X:X|WORD) "
#define NO_NEIGHBOR_CMD2   "no neighbor (A.B.C.D|X:X::X:X|WORD) "
#define NEIGHBOR_ADDR_STR2 "Neighbor address","Neighbor IPv6 address","Neighbor tag"
#else
#define NEIGHBOR_CMD       "neighbor A.B.C.D "
#define NO_NEIGHBOR_CMD    "no neighbor A.B.C.D "
#define NEIGHBOR_ADDR_STR  "IP address"
#define NEIGHBOR_CMD2      "neighbor (A.B.C.D|WORD) "
#define NO_NEIGHBOR_CMD2   "no neighbor (A.B.C.D|WORD) "
#define NEIGHBOR_ADDR_STR2 "Neighbor address","Neighbor tag"
#endif /* HAVE_IPV6 */

/* Allocate a new CLI stree.  */

struct cli_tree *cli_tree_new ();

void
cli_tree_free (struct cli_tree *ctree);

int cli_parse (struct cli_tree *, int, u_char, char *, int, int);
void cli_describe (struct cli *, struct cli_tree *, int cli_mode, u_char,
                   char *, int);
char **cli_complete (struct cli_tree *, int cli_mode, u_char, char *);

int cli_install_gen (struct cli_tree *, int cli_mode, u_char, u_int16_t,
                     struct cli_element *);
int cli_install (struct cli_tree *, int cli_mode, struct cli_element *);
int cli_install_hidden (struct cli_tree *, int cli_mode,
                        struct cli_element *);

int cli_install_imi (struct cli_tree *,
                     int cli_mode,
                     modbmap_t,
                     u_char,
                     u_int16_t,
                     struct cli_element *);

void
cli_set_imi_cmd (struct cli_element *cel,
                 int           new_mode,
                 cfgDataType_e data_type);

void cli_install_shortcut (struct cli_tree *, int cli_mode, char *, char *,
                           char *);

int cli_install_config (struct cli_tree *, int, CLI_CONFIG_FUNC func);

void cli_set_node_flag (struct cli_tree *, int, char *,
                        u_int16_t);
void cli_sort (struct cli_tree *);
void cli_free_arguments (struct cli_tree *);

void cli_mode_exit (struct cli *);
void cli_install_default (struct cli_tree *, int);
void cli_install_default_family (struct cli_tree *, int);

char *cli_interface_resolve (char *, int, char *, char *);

const char *cli_mode_str (int);
const char *cli_prompt_str (int);

/* Utility function.  */
char *argv_concat (char **, int, int);
char *cli_str2int (char *str, u_int32_t *val);
int cmd_str2int (char *, int *);
int cmd_hexstr2int (char *, int *);
int cli_mask_check (struct pal_in4_addr);
char * cli_skip_white_space(char *cmd_str);


#define CLI_INSTALL(Z, M, PM, C)                                              \
    do {                                                                      \
      if ((Z)->protocol == IPI_PROTO_IMI)                                     \
        cli_install_imi ((Z)->ctree, M, PM, PRIVILEGE_NORMAL, 0, C);          \
      else                                                                    \
        cli_install_gen ((Z)->ctree, M, PRIVILEGE_NORMAL, 0, C);              \
    } while (0)

#define CLI_INSTALL_HIDDEN(Z, M, PM, C)                                       \
    do {                                                                      \
      if ((Z)->protocol == IPI_PROTO_IMI)                                     \
        cli_install_imi ((Z)->ctree, M, PM, PRIVILEGE_NORMAL,                 \
                         CLI_FLAG_HIDDEN, C);                                 \
      else                                                                    \
        cli_install_gen ((Z)->ctree, M, PRIVILEGE_NORMAL, CLI_FLAG_HIDDEN, C);\
    } while (0)

#define CLI_GET_INTEGER(NAME,V,STR)                                           \
    do {                                                                      \
      int retv;                                                               \
      (V) = cmd_str2int ((STR), &retv);                                       \
      if (retv < 0)                                                           \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_INTEGER_RANGE(NAME,V,STR,MIN,MAX)                             \
    do {                                                                      \
      int retv;                                                               \
      (V) = cmd_str2int ((STR), &retv);                                       \
      if (retv < 0 || (V) < (MIN) || (V) > (MAX))                             \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_INTEGER64(NAME,V,INT,STR,MIN,MAX)                             \
    do {                                                                      \
      int retv;                                                               \
      int val = 0;                                                            \
      (V) = cmd_str2int ((STR), &retv);                                       \
      pal_mem_cpy (&INT.l[0], &val, 4);                                       \
      pal_mem_cpy (&INT.l[1], &(V), 4);                                       \
      if (retv < 0 || (V) < (MIN) || (V) > (MAX))                             \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_UINT32(NAME,V,STR)                                            \
    do {                                                                      \
      int retv;                                                               \
      if (pal_strncmp ((STR), "-", 1) == 0)                                   \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
      (V) = cmd_str2int ((STR), &retv);                                       \
      if (retv < 0)                                                           \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_UINT32_RANGE(NAME,V,STR,MIN,MAX)                              \
    do {                                                                      \
      char *endptr = NULL;                                                    \
      (V) = pal_strtou32 ((STR), &endptr, 10);                                \
      if (*endptr != '\0' || ((u_int32_t)(MIN) > 0                            \
          && (V) < (u_int32_t)(MIN))                                          \
          || (V) > (u_int32_t)(MAX))                                          \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_IPV4_ADDRESS(NAME,V,STR)                                      \
    do {                                                                      \
      int retv;                                                               \
      retv = pal_inet_pton (AF_INET, (STR), &(V));                            \
      if (!retv)                                                              \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_IPV4_PREFIX(NAME,V,STR)                                       \
    do {                                                                      \
      int retv;                                                               \
      retv = str2prefix_ipv4 ((STR), &(V));                                   \
      if (retv <= 0)                                                          \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#ifdef HAVE_IPV6
#define CLI_GET_IPV6_ADDRESS(NAME,V,STR)                                      \
    do {                                                                      \
      int retv;                                                               \
      retv = pal_inet_pton (AF_INET6, (STR), &(V));                           \
      if (!retv)                                                              \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_IPV6_PREFIX(NAME,V,STR)                                       \
    do {                                                                      \
      int retv;                                                               \
      retv = str2prefix_ipv6 ((STR), &(V));                                   \
      if (retv <= 0)                                                          \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)
#endif /* HAVE_IPV6 */

#define CLI_GET_RMAP_ORIGIN(NAME,V,ARGC,STR)                                  \
    do {                                                                      \
      if ((ARGC) == 0)                                                        \
        (V) = NULL;                                                           \
      else if (pal_strncmp ((STR), "ig", 2) == 0)                             \
        (V) = "igp";                                                          \
      else if (pal_strncmp ((STR), "e", 1) == 0)                              \
        (V) = "egp";                                                          \
      else if (pal_strncmp ((STR), "in", 2) == 0)                             \
        (V) = "incomplete";                                                   \
      else                                                                    \
        {                                                                     \
          cli_out (cli, "%% Invalid %s value\n", NAME);                       \
          return CLI_ERROR;                                                   \
        }                                                                     \
    } while (0)

#define CLI_GET_HEXA_DECIMAL(NAME,V,STR)                                       \
{                                                                              \
  char *endptr = NULL;                                                         \
  (V) = pal_strtou32 ((STR), &endptr, 16);                                     \
  if (*endptr != '\0' || ((V) == ULONG_MAX && errno == ERANGE))                \
    {                                                                          \
      cli_out (cli, "%% Invalid %s value\n", NAME);                            \
      return CLI_ERROR;                                                        \
    }                                                                          \
} 

#endif /* _BGPSDN_CLI_H */
