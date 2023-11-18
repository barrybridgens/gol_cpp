{ pkgs ? import <nixpkgs> {} }:

with pkgs;
mkShell {
  nativeBuildInputs = [
    gcc
    SDL2
    SDL2_ttf
  ];
}