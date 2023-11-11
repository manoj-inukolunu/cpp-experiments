#include <fmt/core.h>
#include <complex>
#include <fstream>
#include <any>
#include <iostream>

#include "manifest-list.hh"

#include "avro/Compiler.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"
#include "avro/Specific.hh"
#include "avro/Generic.hh"
#include "avro/DataFile.hh"
#include "avro/Stream.hh"

avro::ValidSchema loadSchema(const char *filename)
{
    std::ifstream ifs(filename);
    avro::ValidSchema result;
    avro::compileJsonSchema(ifs, result);
    return result;
}

int main()
{
    try
    {
        avro::ValidSchema manifest_list_schema = loadSchema("/mnt/g/cpp-experiments/manifest-list.json");
        std::cout << "Testing Before" << std::endl;
        /* avro::DataFileReader<c::manifest_file> dataFile("G:/iceberg/diamonds_iceberg-20231104T063404Z-001/diamonds_iceberg/metadata/snap-49008598500316325-1-a0a3d5b9-039d-430d-a58b-e48f8d24b997.avro", manifest_list);
        std::cout << "Testing" << std::endl;

        avro::ValidSchema dataSchema = dataFile.dataSchema();
        std::ofstream output("data_schema.json");

        dataSchema.toJson(output);
        output.close(); */

        avro::DataFileWriter<c::manifest_file> dfw("/mnt/g/cpp-experiments/test.avro", manifest_list_schema);
        c::manifest_file c1;
        c1.added_data_files_count = 123;
        c1.added_rows_count = 12;
        c1.added_snapshot_id = 123;
        c1.content = 12;
        c1.deleted_data_files_count = 0;
        c1.deleted_rows_count = 1;
        c1.existing_data_files_count = 1;
        c1.existing_rows_count = 2;
        c1.manifest_length = 12;
        c1.manifest_path = "asdf";
        c1.min_sequence_number = 123;
        c1.partition_spec_id = 12;
        c1.sequence_number = 12;
        
        // std::cout << c1.manifest_path() << std::endl;
        dfw.write(c1);
        std::cout << "Testing After" << std::endl;
        dfw.close();
        std::cout << "Wrote Everything " << std::endl;
        {
            avro::DataFileReader<c::manifest_file> dfr("/mnt/g/cpp-experiments/test.avro",manifest_list_schema);
            c::manifest_file c2;
            while(dfr.read(c2)){
                std:: cout << c2.manifest_path << std::endl;
            }
            std::cout << "Read Everything " << std::endl;
        }
    }
    catch (std::exception &y)
    {
        // std::exception_ptr p = std::current_exception();
        std::cout << " Faile" <<y.what()<< std::endl;
        /* p.__cxa_exception_type()->
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl; */

    }
    return 0;
}