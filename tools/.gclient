solutions = [
  { "name"        : "36.0.1985.125",
    "url"         : "http://src.chromium.org/svn/releases/36.0.1985.125",
    "deps_file"   : "DEPS",
    "managed"     : True,
    "custom_deps" : {
      "src/chrome/test/data" : None,
      "src/third_party/WebKit/LayoutTests": None,
      "src/chrome_frame/tools/test/reference_build/chrome": None,
      "src/chrome/tools/test/reference_build/chrome_mac": None,
      "src/chrome/tools/test/reference_build/chrome_win": None,
      "src/chrome/tools/test/reference_build/chrome_linux": None,
	  "src/third_party/hunspell_dictionaries": None,
    },
    "safesync_url": "",
  },
]
cache_dir = None
