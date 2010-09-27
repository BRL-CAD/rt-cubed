#include <apr_file_io.h>
#include <apr_signal.h>

#include "svn_pools.h"
#include "svn_cmdline.h"
#include "svn_error.h"
#include "svn_opt.h"
#include "svn_utf.h"
#include "svn_subst.h"
#include "svn_path.h"
#include "svn_config.h"
#include "svn_repos.h"
#include "svn_fs.h"
#include "svn_version.h"
#include "svn_props.h"
#include "svn_time.h"
#include "svn_user.h"
#include "svn_client.h"
#include "svn_wc.h"

#include "private/svn_opt_private.h"

#include "svn_private_config.h"

/* Baton for passing option/argument state to a subcommand function. */
  struct svntest_opt_state
  {
	  const char *repository_path;
	  const char *new_repository_path;                  /* hotcopy dest. path */
	  const char *fs_type;                              /* --fs-type */
	  svn_boolean_t pre_1_4_compatible;                 /* --pre-1.4-compatible */
	  svn_boolean_t pre_1_5_compatible;                 /* --pre-1.5-compatible */
	  svn_boolean_t pre_1_6_compatible;                 /* --pre-1.6-compatible */
	  svn_opt_revision_t start_revision, end_revision;  /* -r X[:Y] */
	  svn_boolean_t help;                               /* --help or -? */
	  svn_boolean_t version;                            /* --version */
	  svn_boolean_t incremental;                        /* --incremental */
	  svn_boolean_t use_deltas;                         /* --deltas */
	  svn_boolean_t use_pre_commit_hook;                /* --use-pre-commit-hook */
	  svn_boolean_t use_post_commit_hook;               /* --use-post-commit-hook */
	  svn_boolean_t use_pre_revprop_change_hook;        /* --use-pre-revprop-change-hook */
	  svn_boolean_t use_post_revprop_change_hook;       /* --use-post-revprop-change-hook */
	  svn_boolean_t quiet;                              /* --quiet */
	  svn_boolean_t bdb_txn_nosync;                     /* --bdb-txn-nosync */
	  svn_boolean_t bdb_log_keep;                       /* --bdb-log-keep */
	  svn_boolean_t clean_logs;                         /* --clean-logs */
	  svn_boolean_t bypass_hooks;                       /* --bypass-hooks */
	  svn_boolean_t wait;                               /* --wait */
	  enum svn_repos_load_uuid uuid_action;             /* --ignore-uuid,
							       --force-uuid */
	  const char *parent_dir;

	  const char *config_dir;    /* Overriding Configuration Directory */
  };



/** Main. **/

int
main(int argc, const char *argv[])
{
  svn_error_t *err;
  apr_status_t apr_err;
  apr_allocator_t *allocator;
  apr_pool_t *pool;

  struct svntest_opt_state opt_state;
  int opt_id;

  /* Initialize the app. */
  if (svn_cmdline_init("svnstress", stderr) != EXIT_SUCCESS)
	  return EXIT_FAILURE;


  /* Create our top-level pool.  Use a separate mutexless allocator,
   * given this application is single threaded.
   */
  if (apr_allocator_create(&allocator))
    return EXIT_FAILURE;

  apr_allocator_max_free_set(allocator, SVN_ALLOCATOR_RECOMMENDED_MAX_FREE);

  pool = svn_pool_create_ex(NULL, allocator);
  apr_allocator_owner_set(allocator, pool);

  /* Initialize the FS library. */
  err = svn_fs_initialize(pool);
  if (err)
    return svn_cmdline_handle_exit_error(err, pool, "svnstress: ");

  /* Initialize opt_state. */
  memset(&opt_state, 0, sizeof(opt_state));
  opt_state.start_revision.kind = svn_opt_revision_unspecified;
  opt_state.end_revision.kind = svn_opt_revision_unspecified;

  char *repo_path = "./test_repository";
  const char *full_path = svn_path_canonicalize(repo_path, pool);
  opt_state.repository_path = full_path;

  const char *abs_path;
  char full_repository_url[1024];
  svn_path_get_absolute(&abs_path, repo_path, pool);
  sprintf(full_repository_url,"file://localhost:%s", abs_path);

  int parent=0, child=0, i, result, pid;
  pid = fork();

  for (i = 0; i < 100; i++)
  {
	  switch (pid) {
		  case -1:
			  exit(99);
		  case 0: {
				  /* Have repository, do something with it */

				  svn_client_ctx_t *ctx;
				  if ((err = svn_client_create_context(&ctx, pool)))
					  return svn_cmdline_handle_exit_error(err, pool, "svnstress: ");
				  err = svn_config_get_config(&(ctx->config),
						  opt_state.config_dir, pool);
				  if (err)
				  {
					  /* Fallback to default config if the config directory isn't readable. */
					  if (err->apr_err == APR_EACCES)
					  {
						  svn_handle_warning2(stderr, err, "svn: ");
						  svn_error_clear(err);
					  }
					  else
						  return svn_cmdline_handle_exit_error(err, pool, "svn: ");
				  }

				  /* Next, check out a working copy */
				  char checkout_path[1024];
				  sprintf(checkout_path, "./checkout_%d", i); 
				  const char *full_checkout_path = svn_path_canonicalize(checkout_path, pool);
				  svn_opt_revision_t revision;
				  svn_opt_revision_t peg_revision;
				  revision.kind = svn_opt_revision_head;
				  peg_revision.kind = svn_opt_revision_unspecified;

				  apr_pool_t *subpool;
				  subpool = svn_pool_create(pool);
				  svn_pool_clear(subpool);
				  svn_client_checkout3(NULL, full_repository_url, full_checkout_path, &peg_revision, &revision, svn_depth_infinity, 0, 0, ctx, subpool);

				  /* Increment the file */
				  char file_path[1024];
				  char file_numstr[60];
				  int file_number;
				  FILE *fp;
				  sprintf(file_path,"%s/test_file", full_checkout_path);
				  fp = fopen(file_path, "r");
				  fgets(file_numstr, 50, fp);
				  sscanf(file_numstr, "%d", &file_number);
				  fclose(fp);
				  sprintf(file_numstr,"%d", file_number + 1);
				  fp = fopen(file_path,"w");
				  fputs (file_numstr, fp);
				  fclose (fp);

				  /* Commit the change */
				  apr_array_header_t *targets = apr_array_make(pool, 5, sizeof(const char *));
				  APR_ARRAY_PUSH(targets, const char *) = file_path;
				  svn_pool_clear(subpool);

				  svn_commit_info_t *commit_info = NULL;
				  svn_client_commit4(&commit_info, targets, svn_depth_empty, FALSE, FALSE, NULL, NULL, ctx, subpool);
#if 0
				  /* Perform an update operation on the second repository */
				  svn_pool_clear(subpool);
				  apr_array_header_t *update_targets = apr_array_make(pool, 5, sizeof(const char *));
				  APR_ARRAY_PUSH(update_targets, const char *) = full_checkout_path2;
				  svn_opt_revision_t svnrev;
				  svnrev.kind = svn_opt_revision_unspecified;
				  svn_client_update3(NULL, update_targets, &svnrev, svn_depth_unknown, 0, 0, 0, ctx, subpool);
#endif
				  /* Done, now clean up */
				  svn_pool_destroy(pool);
				  /* Ensure that everything is written to stdout, so the user will
				     see any print errors. */
				  err = svn_cmdline_fflush(stdout);
				  if (err)
				  {
					  svn_handle_error2(err, stderr, FALSE, "svnstress: ");
					  svn_error_clear(err);
					  return EXIT_FAILURE;
				  }
				  return EXIT_SUCCESS;
			  }
		  default:
			  {
				  pid = fork();
			  }
	  }
  }
}

