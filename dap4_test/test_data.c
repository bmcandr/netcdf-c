/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

/**
Test the netcdf-4 data building process.
*/

#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include "netcdf.h"

#undef DEBUG

static void
fail(int code)
{
    if(code != NC_NOERR) {
	fprintf(stderr,"***Fail: %s\n",nc_strerror(code));
	fflush(stderr);
    }
    exit((code==NC_NOERR?EXIT_SUCCESS:EXIT_FAILURE));
}

int
main(int argc, char** argv)
{
    int ret = NC_NOERR;
    char url[4096];
    int ncid;

    /* Skip cmd name */
    argc++;
    argv++;

    if(argc < 2) {
	fprintf(stderr, "too few arguments: t_dmrdata.c <infile> <outfile>\n");
	fail(NC_NOERR);
    }

    /* build the url */
    snprintf(url,sizeof(url),"file://%s#dap4&debug=copy",argv[0]);
    if(argc >= 3) {
        strlcat(url,"&substratename=",sizeof(url));
	strlcat(url,argv[1],sizeof(url));
    }
#ifdef DEBUG
    strlcat(url,"&log",sizeof(url));
#endif

#ifdef DEBUG
    fprintf(stderr,"test_data url=%s\n",url);
#endif
  
    /* Use the open/close mechanism */
    if((ret=nc_open(url,NC_NETCDF4,&ncid))) goto done;
    if((ret=nc_close(ncid))) goto done;

done:
#ifdef DEBUG
    fprintf(stderr,"code=%d %s\n",ret,nc_strerror(ret));
#endif
    return (ret ? 1 : 0);
}
