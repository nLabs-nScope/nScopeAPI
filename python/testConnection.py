try:
    import nscopeapi as nsapi
    ns = nsapi.nScope()
except Exception as e:
    print("Unable to communicate with nScope")
    print(e)
else:
    print("Successfully opened connection to nScope!")