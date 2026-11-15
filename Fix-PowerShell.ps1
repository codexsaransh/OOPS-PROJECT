# ============================================================
# PowerShell Fix Script
# Run this in a normal PowerShell window (NOT as Administrator)
# Double-click it, or right-click > "Run with PowerShell"
# ============================================================

Write-Host "=== PowerShell Fix Script ===" -ForegroundColor Cyan
Write-Host "Running as: $env:USERNAME" -ForegroundColor DarkGray
Write-Host ""

# --- Fix 1: Create missing WindowsPowerShell\Modules folder ---
$psFolder     = Join-Path $env:USERPROFILE "OneDrive\Documents\WindowsPowerShell"
$modulesFolder = Join-Path $psFolder "Modules"

Write-Host "--- Fix 1: WindowsPowerShell folder structure ---" -ForegroundColor Yellow

if (-not (Test-Path $psFolder)) {
    New-Item -ItemType Directory -Path $psFolder -Force | Out-Null
    Write-Host "[FIXED] Created: $psFolder" -ForegroundColor Green
}

if (-not (Test-Path $modulesFolder)) {
    New-Item -ItemType Directory -Path $modulesFolder -Force | Out-Null
    Write-Host "[FIXED] Created: $modulesFolder" -ForegroundColor Green
} else {
    Write-Host "[OK] Modules folder already exists: $modulesFolder" -ForegroundColor Green
}

# --- Fix 2: Create a profile file (CurrentUserCurrentHost) ---
Write-Host ""
Write-Host "--- Fix 2: PowerShell profile file ---" -ForegroundColor Yellow

$profilePath = Join-Path $psFolder "Microsoft.PowerShell_profile.ps1"

if (-not (Test-Path $profilePath)) {
    $profileContent = @'
# PowerShell Profile
# Location: CurrentUserCurrentHost
# -----------------------------------------------

# Friendly prompt showing current path
function prompt {
    $p = (Get-Location).Path
    "PS $p> "
}

# Handy aliases
Set-Alias -Name ll  -Value Get-ChildItem  -ErrorAction SilentlyContinue
Set-Alias -Name cat -Value Get-Content    -ErrorAction SilentlyContinue
Set-Alias -Name which -Value Get-Command  -ErrorAction SilentlyContinue

Write-Host "PS $($PSVersionTable.PSVersion) | Type 'help' for help." -ForegroundColor DarkGray
'@
    Set-Content -Path $profilePath -Value $profileContent -Encoding UTF8
    Write-Host "[FIXED] Created profile: $profilePath" -ForegroundColor Green
} else {
    Write-Host "[OK] Profile already exists: $profilePath" -ForegroundColor Green
}

# --- Fix 3: ExecutionPolicy ---
Write-Host ""
Write-Host "--- Fix 3: Execution Policy ---" -ForegroundColor Yellow

$currentPolicy = Get-ExecutionPolicy -Scope CurrentUser
if ($currentPolicy -eq 'Undefined' -or $currentPolicy -eq 'Restricted') {
    try {
        Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser -Force -ErrorAction Stop
        Write-Host "[FIXED] ExecutionPolicy set to RemoteSigned for CurrentUser" -ForegroundColor Green
    } catch {
        Write-Host "[WARN] Could not set ExecutionPolicy: $_" -ForegroundColor Yellow
        Write-Host "       Try running this script as Administrator if needed." -ForegroundColor DarkGray
    }
} else {
    Write-Host "[OK] ExecutionPolicy is: $currentPolicy" -ForegroundColor Green
}

# --- Verification ---
Write-Host ""
Write-Host "=== Verification ===" -ForegroundColor Cyan

Write-Host ""
Write-Host "PowerShell Version: $($PSVersionTable.PSVersion)" -ForegroundColor White

Write-Host ""
Write-Host "PSModulePath entries:" -ForegroundColor White
$env:PSModulePath -split ';' | ForEach-Object {
    $exists = Test-Path $_
    if ($exists) { Write-Host "  [OK]      $_" -ForegroundColor Green }
    else          { Write-Host "  [MISSING] $_" -ForegroundColor Red }
}

Write-Host ""
Write-Host "Profile files:" -ForegroundColor White
@(
    $PROFILE.CurrentUserCurrentHost,
    $PROFILE.AllUsersCurrentHost,
    $PROFILE.CurrentUserAllHosts,
    $PROFILE.AllUsersAllHosts
) | ForEach-Object {
    $exists = Test-Path $_
    if ($exists) { Write-Host "  [OK]      $_" -ForegroundColor Green }
    else          { Write-Host "  [ABSENT]  $_" -ForegroundColor DarkGray }
}

Write-Host ""
Write-Host "Execution Policy:" -ForegroundColor White
Get-ExecutionPolicy -List | Format-Table -AutoSize

Write-Host ""
Write-Host "=== Done! Open a NEW PowerShell window to see the changes. ===" -ForegroundColor Cyan
Write-Host ""
pause
