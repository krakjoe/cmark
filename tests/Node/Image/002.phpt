--TEST--
CommonMark\Node fetch Image
--FILE--
<?php
$md = <<<MD
![foo](bar.jpg)
MD;

$doc = CommonMark\Parse($md);

$root = $doc->getFirstChild();

$img = $root->getFirstChild();

if ($img instanceof CommonMark\Node\Image) {
	echo "OK";
}
?>
--EXPECT--
OK
