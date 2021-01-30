import time
import sys
import requests as r

try:
    import nscopeapi as nsapi
    ns = nsapi.nScope()
except Exception as e:
    print("Unable to communicate with nScope")
    print(e)
else:
    print("Successfully opened connection to nScope!")
    while True:
        status = ns.getPowerState()
        power_usage = ns.getPowerUsage()
        print(status, power_usage)
        if status == 1:
            res = r.post('http://martino-laptop:1880/power', data={
                'power': power_usage
            })
            time.sleep(0.1)
        elif status == 3:
            print('Overcurrent')
            res = r.post('http://martino-laptop:1880/log', data={
                'message': 'overcurrent',
                'device': 'nscope'
            })
            print(res.status_code)
            break  
        else:
            print('error')
            break
    sys.exit(ns.close())
