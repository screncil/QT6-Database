#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(int argc, TCHAR *argv[]) {

    // Ім'я файлу, яке потрібно знайти
    TCHAR fileName[] = TEXT("MSACCESS.EXE");

    TCHAR accessPath[MAX_PATH];

    // Пошук шляху до MS Access
    if (SearchPath(NULL, fileName, NULL, MAX_PATH, accessPath, NULL) == 0) {
        printf("SearchPath failed (%d).\n", GetLastError());
        return 1;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Запускаємо MS Access без вказання файлу
    if (!CreateProcess(NULL, accessPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Закриваємо дескриптори процесу та потоку
    // CloseHandle(pi.hProcess);
    // CloseHandle(pi.hThread);

    return 0;
    }

