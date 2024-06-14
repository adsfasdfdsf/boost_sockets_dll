// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H
#include "fwd.h"
// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include <boost/function.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/make_shared.hpp>
#include <future>
#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#endif //PCH_H
