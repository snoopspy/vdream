# ---------------------------------------------------------------------------
# vdream
# ---------------------------------------------------------------------------

# vdreamd.lib
cd lib
qmake "CONFIG+=debug" "QT-=gui"
make
make clean
cd ..

# vdreamd_gui.lib
cd lib
qmake "CONFIG+=debug" "QT+=gui" "QT+=widgets"
make
make clean
cd ..

# vdream.lib
cd lib
qmake "CONFIG+=release" "QT-=gui"
make
make clean
cd ..

# vdream_gui.lib
cd lib
qmake "CONFIG+=release" "QT+=gui" "QT+=widgets"
make
# make clean
cd ..

# ---------------------------------------------------------------------------
# app
# ---------------------------------------------------------------------------
qmake
make
