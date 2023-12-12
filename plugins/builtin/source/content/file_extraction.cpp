#include <hex/helpers/fs.hpp>

#include <wolv/io/file.hpp>
#include <romfs/romfs.hpp>

namespace hex::plugin::builtin {

    void extractBundledFiles() {
        for (const auto &romfsPath : romfs::list("auto_extract")) {
            for (const auto &imhexPath : fs::getDataPaths()) {
                const auto path = imhexPath / std::fs::relative(romfsPath, "auto_extract");
                if (wolv::io::fs::exists(path))
                    continue;

                wolv::io::File file(path, wolv::io::File::Mode::Create);
                if (!file.isValid())
                    continue;

                auto data = romfs::get(romfsPath).span<u8>();
                file.writeBuffer(data.data(), data.size());

                if (file.getSize() == data.size())
                    break;
            }

        }
    }

}