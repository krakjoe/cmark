--TEST--
CommonMark\Node fetch Image
--FILE--
<?php
$md = <<<MD
![foo](bar.jpg)
MD;

$doc = CommonMark\Parse($md);

$root = $doc->lastChild;

$img = $root->firstChild;

if ($img instanceof CommonMark\Node\Image) {
	echo "OK";
}
?>
--EXPECT--
OK
