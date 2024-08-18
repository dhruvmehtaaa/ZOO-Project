import subprocess

def run_test(output_file, compile_cmd):
    try:
        print(f"Compiling {output_file}...")
        subprocess.check_call(compile_cmd, shell=True)
        
        print(f"Running {output_file}...")
        subprocess.check_call(f"./{output_file}", shell=True)
    
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")
        print(f"Test failed for {output_file}")
        exit(1)

run_test("test_caching", "gcc -o test_caching caching.c -lcunit")
run_test("test_service", "gcc -o test_service service.c -lcunit")
run_test("test_service_loader", "gcc -o test_service_loader service_loader.c -lcunit -ljson-c")
run_test("test_zoo_loader_fpm", "gcc -o test_zoo_loader_fpm zoo_loader_fpm.c -lcunit -ljson-c")
run_test("test_ulinet", "gcc -o test_ulinet ulinet.c -lcunit -lcurl")
run_test("test_sshapi", "gcc -o test_sshapi sshapi.c -lcunit -lssh2 -I/usr/include -L/usr/lib/x86_64-linux-gnu")
run_test("sqlapi_test", "gcc -o sqlapi_test sqlapi.c -I/usr/include/gdal -lcunit -lgdal")
run_test("service_yaml_test", "gcc -o service_yaml_test service_yaml.c -lcunit -lyaml")
run_test("test_service_internal_python", "gcc -o test_service_internal_python service_internal_python.c -lcunit -lpython3.12 -I/usr/include/python3.12")
run_test("test_service_loader", "gcc -o test_service_loader service_loader.c -lcunit -ldl")
run_test("test_service_json", "gcc -o test_service_json service_json.c -Iinclude -lcunit")
run_test("server_internal_test", "gcc -o server_internal_test server_internal.c -lcunit")
run_test("service_internal_tests", "gcc -o service_internal_tests service_internal.c -lcunit")
run_test("request_parser_test", "gcc -o request_parser_test request_parser.c map_functions.c -lcunit")
run_test("response_print_test", "gcc -o response_print_test response_print.c -lcunit -lxml2 -I/usr/include/libxml2")
run_test("meta_sql", "gcc -o meta_sql meta_sql.c -lcunit")
run_test("test_service_internal_perl", "gcc -o test_service_internal_perl service_internal_perl.c -lcunit $(perl -MExtUtils::Embed -e ccopts) $(perl -MExtUtils::Embed -e ldopts)")
run_test("test_service_internal_java", "gcc -o test_service_internal_java service_internal_java.c -lcunit")
run_test("test_service_internal_r", "gcc -o test_service_internal_r service_internal_r.c -I/usr/share/R/include -lcunit")

print("All tests executed successfully!")
