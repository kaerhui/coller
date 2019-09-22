# 四國軍棋 Qt Implemention

## 簡介

本項目為棋牌游戲 [四國軍棋](https://zh.wikipedia.org/wiki/%E9%99%B8%E8%BB%8D%E6%A3%8B) 的一個實作，使用 Qt5/C++11 寫成，以 LGPL 授權條款發佈。

<img src="screenshot.png" />

目前玩家只能與較為低智的 AI 進行對戰，高智商 AI 以及聯網功能通通沒有，本作者暫時也不打算繼續填坑。不過這些程式碼的耦合程度並不高，其中也預留了聯網對戰可能需要用到的一些接口，如果誰有興趣繼續開發，也不會有太大的困難。

現在本程式支援的 AI 有兩種：「無腦 AI」和「低智商 AI」。前一種非常無腦，代碼很短；後一種稍微有點頭腦，但主要是隨機落子。各位如果覺得這樣玩得不夠爽，也可以參照已有 AI 的程式碼自已寫 AI. 不過要注意的是，我雖然留下了可以創建各種不同 AI 的餘地，但是包含棋局資訊的 `Game` Object 的接口非常原始，如果你想借助我的程式認真開發一個 AI, 請對該 Object 進行二次封裝。

本程式的 GUI 部分使用的是前端技術，介面其實是通過 QtWebkit 顯示 HTML 頁面得到的。由 Javascript 動態渲染 Embbed SVG 畫出棋盤和棋子等等。因此，GUI 交互的反應速度可能會稍慢一點。當然，這跟核心的程序邏輯是完全分離的——如果你對此看不下去了的話，也可以幫我把這部分砍掉重練，換成別的實作。

## 編譯及安裝

編譯方式同一般的 Qt 程式一樣：

```
$ qmake
$ make
```

Archlinux 使用者可以直接通過 AUR 安裝：

```
$ yaourt -S gwankei-git
```