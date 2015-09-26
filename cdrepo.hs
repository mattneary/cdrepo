module Main where

import System.Environment
import System.Process
import Data.List
import System.Directory

main =
  do (script:args) <- getArgs
     scriptContents <- readFile script
     scriptParent <- canonicalizePath (script ++ "/..")
     let (_:scriptLines) = lines scriptContents
     let skipped = intercalate "\n" scriptLines
     (_, _, _, p) <- createProcess (proc "/bin/bash" $ ["-c", skipped, scriptParent] ++ args)
     waitForProcess p

