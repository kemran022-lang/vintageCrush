VINTAGE CRUSH — исходный проект VST3 для Windows / FL Studio 21

Важно: это НЕ готовый .vst3-файл. Архив содержит исходный проект и GitHub Actions workflow,
который собирает VST3 на Windows. Сборка запускается после загрузки проекта в GitHub.

Параметры:
- Формат: VST3, x64
- Плагин: Vintage Crush
- Эффекты: Warm Vintage, Dirty Crunch, Vinyl Texture / Noise
- Управление: Warm, Crunch, Vinyl, Noise, Tone, Mix, Output, Analog/Vintage, Random

Как получить файл:
1. Создай новый репозиторий на GitHub.
2. Загрузи в него всё содержимое этого архива, включая скрытую папку .github.
3. Открой вкладку Actions и запусти workflow "Build Vintage Crush".
4. После успешной сборки скачай artifact "VintageCrush-Windows-VST3".
5. Извлеки папку Vintage Crush.vst3 и помести её в:
   C:\Program Files\Common Files\VST3
6. В FL Studio открой Plugin Manager и выполни Find installed plugins.

Нужен GitHub-аккаунт. Не загружай проект в публичный репозиторий, если хочешь сохранить его приватным.
