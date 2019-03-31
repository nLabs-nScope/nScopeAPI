{
    "targets": [{
        "target_name": "nscopeapi",
        "sources": [ "./node-module.c" ],
        "include_dirs": [ "../include"],
        "libraries": ["-L<(module_root_dir)/../lib/mac","-lnscopeapi","-Wl,-rpath,node_modules/nscopeapi/lib/mac"],
    }]
}
