{
    "targets": [{
        "target_name": "nscopeapi",
        "sources": [ "./node-module.c" ],
        "include_dirs": [ "../include"],
        "copies":
        [
            {
               'destination': '<(module_root_dir)',
               'files': ['<(module_root_dir)/../lib/']
            }
        ],
        "libraries": ["-L<(module_root_dir)/lib/mac","-lnscopeapi","-Wl,-rpath,node_modules/nscopeapi/lib/mac"],
    }]
}
