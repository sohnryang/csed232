# CSED232: Object Oriented Programming

[![CMake](https://github.com/sohnryang/csed232/actions/workflows/cmake.yml/badge.svg)](https://github.com/sohnryang/csed232/actions/workflows/cmake.yml)

> C++ 기초부터 차근차근

객체지향프로그래밍 과제 코드

| ASSN | 내용                                       |
| ---- | ------------------------------------------ |
| 1    | 기본적인 C++ 문법 연습                     |
| 2    | Linked list를 사용한 pivot table 만들기    |
| 3    | 상속, 다형성을 이용한 ascii art 프로그램   |
| 4    | C++의 `std::shared_pointer<T>` 구현해 보기 |
| 5    | 2048 게임 구현 (with GUI)                  |

## 빌드 방법

```shell
$ mkdir build
$ cd build
$ cmake -G "Unix Makefiles" ..
$ make
```

기본 설정에서는 Qt 6가 필요한 ASSN5와 LLVM libfuzzer를 사용하는 fuzz test 코드가 빌드되지 않습니다. ASSN5를 빌드하려면 `export BUILD_QT=1`을, fuzz test 코드를 빌드하려면 `export BUILD_FUZZ_TESTS=1`을 `cmake` 명령어 전에 실행해서 환경 변수를 세팅해야 합니다.

> Note: Qt 6를 빌드하기 위해서 `CMAKE_PREFIX_PATH` 환경변수도 설정해야 할 수 있습니다. macOS에서 libfuzzer를 사용하기 위해서는 XCode에 포함된 `clang` 대신 homebrew 등에서 `clang` 설치가 필요할 수 있습니다.

빌드된 결과물은 `build/bin`에 저장되고, 단위 테스트는 `ctest` 명령어를 실행해서 결과를 확인할 수 있습니다.

`cmake`에서 `-G` 옵션에 `Unix Makefiles` 대신 다른 옵션을 주어 원하는 빌드 도구를 사용할 수도 있습니다. 빠른 빌드를 원한다면 `Ninja`를 사용하는 것을 권장합니다.

## Tips & Tricks

- 작은 단위로 만들고 각각을 테스트하세요. 전체 코드를 다 짠 다음 테스팅/디버깅하는 것은 비효율적입니다.
  - 단위 테스트를 하는 것이 좋은데, CMake 기반으로 프로젝트를 만든다면 [GoogleTest](http://google.github.io/googletest/), [CppUnit](https://freedesktop.org/wiki/Software/cppunit/) 등 다양한 C++ 단위 테스트 프레임워크를 연동해서 사용할 수 있습니다. 여기서는 GoogleTest를 사용했습니다.
  - Visual Studio 기반으로 프로젝트를 만든다면 VS에 내장된 단위 테스트 프레임워크를 사용할 수 있습니다. [공식 문서](https://learn.microsoft.com/ko-kr/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2022)를 참고하세요.
- C/C++의 메모리 관련 버그와 (주로 이들로 인해 일어나는) undefined behavior는 생각보다 찾기 어려울 뿐더러, [비직관적인 결과를](https://predr.ag/blog/falsehoods-programmers-believe-about-undefined-behavior/)를 일으키기도 합니다.
  - 눈대중으로 디버깅하기보다는 단위 테스트로 엣지 케이스를 확인해 보고, `valgrind`나 AddressSanitizer 등 자동화된 도구로 검사하는 방법을 쓰는 것이 도움이 됩니다.
- C++ STL은 다양한 함수와 클래스가 잘 구현되어 있습니다. 따로 제한이 없다면 직접 자료구조나 함수 등을 구현하는 것보다 이미 구현된 것들을 사용하는 것이 더 좋습니다.
