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
        "conditions": [
            ["OS=='mac'",
            {
                "link_settings" : {
                    "libraries": [
                        "-L<(module_root_dir)/lib/mac",
                        "-Wl,-rpath,node_modules/nscopeapi/lib/mac"
                    ]
                }
            }],
            ["OS=='linux'",
            {
                "conditions": [
                    ["'<!(node -e \"console.log(require('process').arch);\")'=='arm64'",
                    {                
                        "link_settings" : {
                            "libraries": [
                                "-L<(module_root_dir)/lib/linux_arm64",
                                "-Wl,-rpath,node_modules/nscopeapi/lib/linux_arm64"
                            ]
                        }
                    }],
                    ["'<!(node -e \"console.log(require('process').arch);\")'=='arm'",
                    {                
                        "link_settings" : {
                            "libraries": [
                                "-L<(module_root_dir)/lib/linux_armhf",
                                "-Wl,-rpath,node_modules/nscopeapi/lib/linux_armhf"
                            ]
                        }
                    }],
                    ["'<!(node -e \"console.log(require('process').arch);\")'=='x64'",
                    {                
                        "link_settings" : {
                            "libraries": [
                                "-L<(module_root_dir)/lib/linux_amd64",
                                "-Wl,-rpath,node_modules/nscopeapi/lib/linux_amd64"
                            ]
                        }
                    }],
                    ["'<!(node -e \"console.log(require('process').arch);\")'=='x32'",
                    {                
                        "link_settings" : {
                            "libraries": [
                                "-L<(module_root_dir)/lib/linux_i386",
                                "-Wl,-rpath,node_modules/nscopeapi/lib/linux_i386"
                            ]
                        }
                    }]
                ]

            }],
        ]
    }]
}
