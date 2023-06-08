# Keyboard tweaks

## Keyboard layout

### United States - International - Dedeaded - Swedish

- US-INTL-KCH-SWE.klc

A variation on the US International keymap. Swedish characters are moved to a,
e and o, which are the characters I use if umlauts aren't available. The US
international keymap uses dead-keys which I despise. The dead-key function is
moved to holding control + normal keyboard combination. This causes warnings
when validating, but is perfectly usable.

    WARNING: ^ (U+005e) is already defined more than once on the keyboard (on VK_6, ShiftState 'Ctl+Alt' and VK_6, ShiftState 'Shift').
    WARNING: ` (U+0060) is already defined more than once on the keyboard (on VK_OEM_3, ShiftState 'Ctl+Alt' and VK_OEM_3, ShiftState 'Base').
    WARNING: ~ (U+007e) is already defined more than once on the keyboard (on VK_OEM_3, ShiftState 'Shift+Ctl+Alt' and VK_OEM_3, ShiftState 'Shift').
    WARNING: ' (U+0027) is already defined more than once on the keyboard (on VK_OEM_7, ShiftState 'Ctl+Alt' and VK_OEM_7, ShiftState 'Base').
    WARNING: " (U+0022) is already defined more than once on the keyboard (on VK_OEM_7, ShiftState 'Shift+Ctl+Alt' and VK_OEM_7, ShiftState 'Shift').

### United States - Swedish

- US-KCH-SWE.klc

Standard US ANSI layout with Swedish umlauts on AltGr(+Shift) a, e and o.


## Building

To compile and install, use [Microsoft Keyboard Layout Creator][msklc]. Not available through winget.

It requires .NET Framework 3.5 to be installed. Start `powershell` with administrator privileges.

```ps
    Enable-WindowsOptionalFeature -Online -FeatureName "NetFx3"
```

Open MSKLC and load the layout. Under `project` run `Build DLL and Setup Package`.

Open the directory created, install the layout via `setup`.

[msklc]: https://www.microsoft.com/en-us/download/details.aspx?id=102134

## Using

The keymaps are installed extra keyboard layouts on English (United States).
