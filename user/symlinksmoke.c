#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Minimal Step-6 smoke test for symlink() creation only.
// Full type/target checks need O_NOFOLLOW (Step 7).
int
main(int argc, char *argv[])
{
  unlink("smokelink");
  unlink("smokelink2");

  if (symlink("dangling-target", "smokelink") != 0) {
    printf("symlinksmoke: dangling create failed\n");
    exit(1);
  }
  if (symlink("other", "smokelink") != -1) {
    printf("symlinksmoke: overwrite existing should fail\n");
    exit(1);
  }
  if (symlink("also-dangling", "smokelink2") != 0) {
    printf("symlinksmoke: second create failed\n");
    exit(1);
  }

  unlink("smokelink");
  unlink("smokelink2");
  printf("symlinksmoke: OK\n");
  exit(0);
}
