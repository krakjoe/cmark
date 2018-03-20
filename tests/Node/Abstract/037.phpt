--TEST--
CommonMark\Node caching
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$heading = $doc->firstChild;
$heading->parent == $heading->parent;
echo "OK";
?>
--EXPECT--
OK
