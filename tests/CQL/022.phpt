--TEST--
CommonMark\CQL constraint Link
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
[link](here)
text here
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Link)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Link) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

