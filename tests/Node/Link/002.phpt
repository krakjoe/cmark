--TEST--
CommonMark\Node fetch Link
--FILE--
<?php
$md = <<<MD
[link](/url "title")
MD;

$doc = CommonMark\Parse($md);

$root = $doc->firstChild;

$img = $root->firstChild;

if ($img instanceof CommonMark\Node\Link) {
	echo "OK";
}
?>
--EXPECT--
OK
