--TEST--
CommonMark\CQL constraint Image
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
![link](here)
text here
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Image)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Image) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

