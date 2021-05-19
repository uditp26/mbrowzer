cmake_minimum_required(VERSION 3.20.1)

set(this src_dom)

set(dom_sources
    Element.cpp
    Node.cpp
    Text.cpp
)

add_library(${this} STATIC ${dom_sources} ${dom_headers})