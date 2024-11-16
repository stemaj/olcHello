# olcHello
Example project to test the integration of olcTemplate.

# Add Template
git submodule add git@github.com:stemaj/olcTemplate.git olcTemplate
git submodule update --init --recursive

# Build Project Files wih GENie
~/GENie/bin/linux/genie xcode15
~/GENie/bin/linux/genie vs2022
~/GENie/bin/linux/genie gmake
~/GENie/bin/linux/genie --os=macosx gmake
~/GENie/bin/linux/genie jcdb

# Emscripten
./emsdk install 2.0.34
./emsdk activate 2.0.34